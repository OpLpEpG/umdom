/*
 * Copyright (c) 2018 Kokoon Technology Limited
 * Copyright (c) 2019 Song Qiang <songqiang1304521@gmail.com>
 * Copyright (c) 2019 Endre Karlson
 * Copyright (c) 2020 Teslabs Engineering S.L.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT  st_stm32f1_adc1_ac

#include <errno.h>

#include <drivers/adc.h>
#include <drivers/gpio.h>
#include <device.h>
#include <kernel.h>
#include <init.h>
#include <soc.h>
#include <stm32_ll_adc.h>
#include <stm32_ll_tim.h>
#include <stm32_ll_dma.h>
#include "adc_context.h"

#define LOG_LEVEL CONFIG_ADCAC_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(adc1_ac_stm32f1);

#include <drivers/clock_control/stm32_clock_control.h>
#include <pinmux/pinmux_stm32.h>

#if !defined(CONFIG_SOC_SERIES_STM32F1X)
#  error "ADC AC driver only for STM32F1X series."
#endif
#define SCAN_COUNT (4*CONFIG_ADC_STM32_AC_CURRENT_OVERSAMPLING)

#define ADCACTGR DT_STRING_UPPER_TOKEN(DT_NODELABEL(adc1), trigger)
#if (ADCACTGR == tim2_cc2)
# define ADC_TIMER timers2
# define ADC_TIMER_CH LL_TIM_CHANNEL_CH2
# define ADC_TRIG  LL_ADC_REG_TRIG_EXT_TIM2_CH2 
#elif (ADCACTGR == tim4_cc4)
# define ADC_TIMER timers4
# define ADC_TIMER_CH LL_TIM_CHANNEL_CH4
# define ADC_TRIG  LL_ADC_REG_TRIG_EXT_TIM4_CH4 
#elif (ADCACTGR == tim1_cc1)
# define ADC_TIMER timers1
# define ADC_TIMER_CH LL_TIM_CHANNEL_CH1
# define ADC_TRIG  LL_ADC_REG_TRIG_EXT_TIM1_CH1 
#elif (ADCACTGR == tim1_cc2)
# define ADC_TIMER timers1
# define ADC_TIMER_CH LL_TIM_CHANNEL_CH2
# define ADC_TRIG  LL_ADC_REG_TRIG_EXT_TIM1_CH2 
#elif (ADCACTGR == tim1_cc3)
# define ADC_TIMER timers1
# define ADC_TIMER_CH LL_TIM_CHANNEL_CH3
# define ADC_TRIG  LL_ADC_REG_TRIG_EXT_TIM1_CH3 
#else
# error "ADC trgigger mast bee defined"
#endif

#if !defined(CONFIG_SOC_SERIES_STM32F0X) && \
	!defined(CONFIG_SOC_SERIES_STM32G0X) && \
	!defined(CONFIG_SOC_SERIES_STM32L0X)
#define RANK(n)		LL_ADC_REG_RANK_##n
static const uint32_t table_rank[] = {
	RANK(1),
	RANK(2),
	RANK(3),
	RANK(4),
	RANK(5),
	RANK(6),
	RANK(7),
	RANK(8),
	RANK(9),
	RANK(10),
	RANK(11),
	RANK(12),
	RANK(13),
	RANK(14),
	RANK(15),
	RANK(16),
};

#define SEQ_LEN(n)	LL_ADC_REG_SEQ_SCAN_ENABLE_##n##RANKS
static const uint32_t table_seq_len[] = {
	LL_ADC_REG_SEQ_SCAN_DISABLE,
	SEQ_LEN(2),
	SEQ_LEN(3),
	SEQ_LEN(4),
	SEQ_LEN(5),
	SEQ_LEN(6),
	SEQ_LEN(7),
	SEQ_LEN(8),
	SEQ_LEN(9),
	SEQ_LEN(10),
	SEQ_LEN(11),
	SEQ_LEN(12),
	SEQ_LEN(13),
	SEQ_LEN(14),
	SEQ_LEN(15),
	SEQ_LEN(16),
};
#endif

#define SMP_TIME(x, y)		LL_ADC_SAMPLINGTIME_##x##CYCLE##y
/*
 * Conversion time in ADC cycles. Many values should have been 0.5 less,
 * but the adc api system currently does not support describing 'half cycles'.
 * So all half cycles are counted as one.
 */
#if defined(CONFIG_SOC_SERIES_STM32F0X) || defined(CONFIG_SOC_SERIES_STM32F1X)
static const uint16_t acq_time_tbl[8] = {2, 8, 14, 29, 42, 56, 72, 240};
static const uint32_t table_samp_time[] = {
	SMP_TIME(1,   _5),
	SMP_TIME(7,   S_5),
	SMP_TIME(13,  S_5),
	SMP_TIME(28,  S_5),
	SMP_TIME(41,  S_5),
	SMP_TIME(55,  S_5),
	SMP_TIME(71,  S_5),
	SMP_TIME(239, S_5),
};
#endif

/* External channels (maximum). */
#define STM32_CHANNEL_COUNT		10
#define AC_CHANNEL_T int16_t

static uint16_t __aligned(4) adc_repeat_buffer[STM32_CHANNEL_COUNT];// = {1,2,3,4,5,6,7,8,9,10};
static int32_t __aligned(4) summ_X2[STM32_CHANNEL_COUNT];
static int32_t __aligned(4) summ_X3[STM32_CHANNEL_COUNT];

struct adc_ac_stm32_data {
	struct adc_context ctx;
	const struct device *dev;
	AC_CHANNEL_T *sequence_buffer; 
	uint16_t *repeat_buffer;
	int32_t *summX2_buffer;
	int32_t *summX3_buffer;
	uint16_t summ_counter;
	uint8_t channel_count;
};

struct adc_ac_stm32_cfg {
	/** pinctrl configurations. */
	const struct soc_gpio_pinctrl *pinctrl;
	/** Number of pinctrl configurations. */
	size_t pinctrl_len;
	//** Timer part */
	/** Timer instance. */
	TIM_TypeDef *timer;
	/** Clock configuration. */
	const struct stm32_pclken pclken_timer;
};
static void adc_stm32_reset_buffers(struct adc_ac_stm32_data *data)
{	
	data->repeat_buffer = adc_repeat_buffer;
	data->summX2_buffer = summ_X2;
	data->summX3_buffer = summ_X3;
	data->ctx.sampling_index = 0;
}

static int check_buffer_size(const struct adc_sequence *sequence,
			     uint8_t active_channels)
{
	size_t needed_buffer_size;

	needed_buffer_size = active_channels * sizeof(AC_CHANNEL_T);
	
	if (sequence->buffer_size < needed_buffer_size) {
		LOG_ERR("Provided buffer is too small (%u/%u)",
				sequence->buffer_size, needed_buffer_size);
		return -ENOMEM;
	}

	return 0;
}

static void adc_stm32_stop_conversion(const struct device *dev)
{
	const struct adc_ac_stm32_cfg *config = dev->config;
	 TIM_TypeDef *timer = config->timer;
	LL_TIM_DisableCounter(timer);
	LL_ADC_REG_StopConversionExtTrig(ADC1);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
	LOG_DBG("Stop conversion");
}

static void adc_stm32_start_conversion(const struct device *dev)
{
	const struct adc_ac_stm32_cfg *config = dev->config;
	struct adc_ac_stm32_data *data = dev->data;
	 TIM_TypeDef *timer = config->timer;

	LOG_DBG("Starting conversion");

    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1,
                          LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
                          (uint32_t) data->repeat_buffer,
                          LL_DMA_DIRECTION_PERIPH_TO_MEMORY);  	
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, data->channel_count);					  
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_ADC_REG_StartConversionExtTrig(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
	LL_TIM_EnableCounter(timer);
}

static int start_read(const struct device *dev,
		      const struct adc_sequence *sequence)
{
	struct adc_ac_stm32_data *data = dev->data;	
	int err;

	uint32_t channels = sequence->channels;
	if ((channels >= BIT(STM32_CHANNEL_COUNT)) || (channels == 0)) {
		LOG_ERR("Only 1-10 channel supported");
		return -ENOTSUP;
	}
	if (sequence->options){
		LOG_ERR("sequence options NOT supported");
		return -ENOTSUP;

	}
	data->sequence_buffer = sequence->buffer;
	uint8_t index = 0; 
	uint8_t channel_count = 0;

	while (channels > 0)
	{
		if (channels & 1)
		{
			uint32_t channel = __LL_ADC_DECIMAL_NB_TO_CHANNEL(index);
			LL_ADC_REG_SetSequencerRanks(ADC1, table_rank[channel_count], channel);
			channel_count++;
		}
		index++;
		channels >>= 1;
	}
	LL_ADC_REG_SetSequencerLength(ADC1, table_seq_len[channel_count-1]);

	data->channel_count = channel_count;
	data->summ_counter = 0;
	memset(summ_X2, 0, sizeof(summ_X2));
	memset(summ_X3, 0, sizeof(summ_X3));
	adc_stm32_reset_buffers(data);

	err = check_buffer_size(sequence, data->channel_count);
	if (err) {
		return err;
	}
	adc_context_start_read(&data->ctx, sequence);

	return adc_context_wait_for_completion(&data->ctx);
}

// static void adc_context_enable_timer(struct adc_context *ctx)
// {

// }
// static void adc_context_disable_timer(struct adc_context *ctx)
// {

// }

static void   adc_context_start_sampling(struct adc_context *ctx)
{
	struct adc_ac_stm32_data *data =
		CONTAINER_OF(ctx, struct adc_ac_stm32_data, ctx);

	// data->repeat_buffer = data->buffer;

	adc_stm32_start_conversion(data->dev);
}

// static void adc_context_update_buffer_pointer(struct adc_context *ctx,
// 					      bool repeat_sampling)
// {
	// struct adc_ac_stm32_data *data =
	// 	CONTAINER_OF(ctx, struct adc_ac_stm32_data, ctx);

	// if (repeat_sampling) {
		// data->buffer = data->repeat_buffer;
	// }
// }

/**
 * Obtain timer clock speed.
 *
 * @param pclken  Timer clock control subsystem.
 * @param tim_clk Where computed timer clock will be stored.
 *
 * @return 0 on success, error code otherwise.
 */
static int get_tim_clk(const struct stm32_pclken *pclken, uint32_t *tim_clk)
{
	int r;
	const struct device *clk;
	uint32_t bus_clk, apb_psc;

	clk = DEVICE_DT_GET(STM32_CLOCK_CONTROL_NODE);

	r = clock_control_get_rate(clk, (clock_control_subsys_t *)pclken,
				   &bus_clk);
	if (r < 0) {
		return r;
	}

	if (pclken->bus == STM32_CLOCK_BUS_APB1) {
		apb_psc = STM32_APB1_PRESCALER;
	}
	else {
		apb_psc = STM32_APB2_PRESCALER;
	}

	/*
	 * If the APB prescaler equals 1, the timer clock frequencies
	 * are set to the same frequency as that of the APB domain.
	 * Otherwise, they are set to twice (×2) the frequency of the
	 * APB domain.
	 */
	if (apb_psc == 1u) {
		*tim_clk = bus_clk;
	} else {
		*tim_clk = bus_clk * 2u;
	}
	return 0;
}


static void dma_adc_stm32_ac_summ(struct adc_ac_stm32_data *data, uint16_t last_index)
{
	switch (data->summ_counter & 3){
	  	case 0:
			while (data->ctx.sampling_index < last_index) 
			{
				*data->summX3_buffer++ += *data->repeat_buffer++;
				data->ctx.sampling_index++;
			}
	  	break;
	  	case 1:
			while (data->ctx.sampling_index < last_index) 
			{
				*data->summX2_buffer++ += *data->repeat_buffer++;
				data->ctx.sampling_index++;
			}
	  	break;
	  	case 2:
			while (data->ctx.sampling_index < last_index)
			{
				*data->summX3_buffer++ -= *data->repeat_buffer++;
				data->ctx.sampling_index++;
			} 
	  	break;
	  	case 3:
			while (data->ctx.sampling_index < last_index) 
			{
				*data->summX2_buffer++ -= *data->repeat_buffer++;
				data->ctx.sampling_index++;
			}
	  	break;
	};
	// LOG_DBG("%d", data->ctx.sampling_index);
}

static float fast_sqrt( float number )
{	
	const float x2 = number * 0.5F;
	const float threehalfs = 1.5F;

	union {
		float f;
		uint32_t i;
	} conv  = { .f = number };
	conv.i  = 0x5f3759df - ( conv.i >> 1 );
	conv.f  *= threehalfs - ( x2 * conv.f * conv.f );
	conv.f  *= threehalfs - ( x2 * conv.f * conv.f );
	conv.f  *= threehalfs - ( x2 * conv.f * conv.f );
	return 1/conv.f;
}

static void dma_adc_stm32_ac_result(struct adc_ac_stm32_data *data)
{
	int32_t *psin = summ_X2;
	int32_t *pcos = summ_X3;
	for (size_t i = 0; i < data->channel_count; i++)
	{
		float sn = (float)*psin++/(SCAN_COUNT/2);
		float cs = (float)*pcos++/(SCAN_COUNT/2);
		*data->sequence_buffer++ = fast_sqrt(sn*sn+cs*cs);
	}	
}

static void dma_adc_stm32_isr(const struct device *dev)
{
	struct adc_ac_stm32_data *data = (struct adc_ac_stm32_data *)dev->data;
	uint32_t flag_it = LL_DMA_ReadReg(DMA1, ISR);
#ifdef CONFIG_DEBUG_LED	
	static const struct device *led = DEVICE_DT_GET(DT_NODELABEL(gpioc));	
	gpio_pin_toggle(led, 13);
#endif	 
	if (flag_it & DMA_FLAG_HT1)
	{
		LL_DMA_ClearFlag_HT1(DMA1);
		uint16_t len = data->channel_count - (LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) >> 1);
		dma_adc_stm32_ac_summ(data, len);
	}
	else if (flag_it & DMA_FLAG_TC1)
	{
		LL_DMA_ClearFlag_TC1(DMA1);
		dma_adc_stm32_ac_summ(data, data->channel_count);
		adc_stm32_reset_buffers(data);
		data->summ_counter++;
		if (data->summ_counter == SCAN_COUNT)
		{
			adc_stm32_stop_conversion(dev);
			dma_adc_stm32_ac_result(data);
			adc_context_complete(&data->ctx, 0);
			LOG_DBG("ISR triggered.");
		}
	}
	else if (flag_it & DMA_FLAG_TE1)
	{
		LL_DMA_ClearFlag_TE1(DMA1);
		adc_stm32_stop_conversion(dev);
		adc_context_complete(&data->ctx, -EIO);
	}
}

static int adc_stm32_read(const struct device *dev,
			  const struct adc_sequence *sequence)
{
	struct adc_ac_stm32_data *data = dev->data;
	int error;

	adc_context_lock(&data->ctx, false, NULL);
	error = start_read(dev, sequence);
	adc_context_release(&data->ctx, error);

	return error;
}

#ifdef CONFIG_ADC_ASYNC
static int adc_stm32_read_async(const struct device *dev,
				 const struct adc_sequence *sequence,
				 struct k_poll_signal *async)
{
	struct adc_ac_stm32_data *data = dev->data;
	int error;

	adc_context_lock(&data->ctx, true, async);
	error = start_read(dev, sequence);
	adc_context_release(&data->ctx, error);

	return error;
}
#endif

static int adc_stm32_check_acq_time(uint16_t acq_time)
{
	for (int i = 0; i < 8; i++) {
		if (acq_time == ADC_ACQ_TIME(ADC_ACQ_TIME_TICKS,
					     acq_time_tbl[i])) {
			return i;
		}
	}

	if (acq_time == ADC_ACQ_TIME_DEFAULT) {
		return 0;
	}

	LOG_ERR("Conversion time not supportted.");
	return -EINVAL;
}

static void adc_stm32_setup_speed(const struct device *dev, uint8_t id,
				  uint8_t acq_time_index)
{
	LL_ADC_SetChannelSamplingTime(ADC1,
		__LL_ADC_DECIMAL_NB_TO_CHANNEL(id),
		table_samp_time[acq_time_index]);
}

static int adc_stm32_channel_setup(const struct device *dev,
				   const struct adc_channel_cfg *channel_cfg)
{
	int acq_time_index;

	if (channel_cfg->channel_id >= STM32_CHANNEL_COUNT) {
		LOG_ERR("Channel %d is not valid", channel_cfg->channel_id);
		return -EINVAL;
	}

	acq_time_index = adc_stm32_check_acq_time(channel_cfg->acquisition_time);

	if (acq_time_index < 0) {
		return acq_time_index;
	}
	if (channel_cfg->differential) {
		LOG_ERR("Differential channels are not supported");
		return -EINVAL;
	}
	if (channel_cfg->gain != ADC_GAIN_1) {
		LOG_ERR("Invalid channel gain");
		return -EINVAL;
	}
	if (channel_cfg->reference != ADC_REF_INTERNAL) {
		LOG_ERR("Invalid channel reference");
		return -EINVAL;
	}

	adc_stm32_setup_speed(dev, channel_cfg->channel_id, acq_time_index);

	LOG_DBG("Channel setup succeeded!");

	return 0;
}

static int adc_stm32_init(const struct device *dev)
{
	struct adc_ac_stm32_data *data = dev->data;
	const struct adc_ac_stm32_cfg *config = dev->config;
	const struct device *clk = DEVICE_DT_GET(STM32_CLOCK_CONTROL_NODE);
	// ADC_TypeDef *adc = (ADC_TypeDef *)config->base;
	TIM_TypeDef *timer = (TIM_TypeDef *)config->timer;
	// DMA_TypeDef *dma = (DMA_TypeDef *)config->dma;
  	LL_TIM_InitTypeDef TIM_InitStruct = {0};
  	LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
	int err;
	uint32_t timer_clk;

	LOG_DBG("ADC Initializing....");

	data->dev = dev;
	/** ADC setup */
	struct stm32_pclken pa = {
		.enr = DT_CLOCKS_CELL(DT_NODELABEL(adc1), bits),		
		.bus = DT_CLOCKS_CELL(DT_NODELABEL(adc1), bus),			
	};
	if (clock_control_on(clk,
		(clock_control_subsys_t *) &pa) != 0) {
		return -EIO;
	}
	/* Configure dt provided device signals when available */
	err = stm32_dt_pinctrl_configure(config->pinctrl,
					 config->pinctrl_len,
					 (uint32_t)ADC1);
	if (err < 0) {
		LOG_ERR("ADC pinctrl setup failed (%d)", err);
		return err;
	}
	LL_ADC_Enable(ADC1);

	/** Timer setup and start */
	if (clock_control_on(clk,
		(clock_control_subsys_t *) &config->pclken_timer) != 0) {
		return -EIO;
	}
	err = get_tim_clk(&config->pclken_timer, &timer_clk);
	if (err < 0) {
		LOG_ERR("Could not obtain timer clock (%d)", err);
		return err;
	}

	err = timer_clk % 1000000;
	if (err > 0)
	{
		LOG_ERR("ADC timer setup failed clk %% 1Mhz = (%d)", err);
		return -EIO;
	} 
	uint32_t prescaler = timer_clk / 1000000;
	if (prescaler == 0)
	{
		LOG_ERR("ADC timer prescaler setup failed");
		return -EIO;
	}
    TIM_InitStruct.Prescaler = prescaler-1; //1us tick
   	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  	TIM_InitStruct.Autoreload = 2500-1;		//2500us toggle -> 5000us period = 5ms -200Hz	
  	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;

	if (LL_TIM_Init(timer, &TIM_InitStruct) != SUCCESS) {
		LOG_ERR("Could not initialize ADC timer");
		return -EIO;
	}
	LL_TIM_DisableARRPreload(timer);
  	LL_TIM_SetClockSource(timer, LL_TIM_CLOCKSOURCE_INTERNAL);

  	TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_TOGGLE;
  	TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  	TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  	TIM_OC_InitStruct.CompareValue = 1;
  	TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;

	if (LL_TIM_OC_Init(timer, ADC_TIMER_CH, &TIM_OC_InitStruct) != SUCCESS) {
		LOG_ERR("Could not initialize ADC timer channel output");
		return -EIO;
	}
	LL_TIM_OC_DisableFast(timer, ADC_TIMER_CH);
  	LL_TIM_SetTriggerOutput(timer, LL_TIM_TRGO_RESET);
  	LL_TIM_DisableMasterSlaveMode(timer);
	LL_TIM_CC_EnableChannel(timer, ADC_TIMER_CH);


	/** dma setup */
	IRQ_CONNECT(DT_IRQN(DT_NODELABEL(dma1)),				
		    DT_IRQ(DT_NODELABEL(dma1), priority),			
		    dma_adc_stm32_isr, DEVICE_DT_GET(DT_NODELABEL(adc1)), 0);	

	struct stm32_pclken pd = {
		.enr = DT_CLOCKS_CELL(DT_NODELABEL(dma1), bits),		
		.bus = DT_CLOCKS_CELL(DT_NODELABEL(dma1), bus),			
	};
	if (clock_control_on(clk,
		(clock_control_subsys_t *) &pd) != 0) {
		return -EIO;
	}
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);
  	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
  	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
  	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
  	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);
  	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_HT(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
	irq_enable(DT_IRQN(DT_NODELABEL(dma1)));	

	/* Calibration of F1 must starts after two cycles after ADON is set. */
	LL_ADC_StartCalibration(ADC1);
	LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_ENABLE);
	LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
	LL_ADC_REG_SetTriggerSource(ADC1, ADC_TRIG);
	adc_context_unlock_unconditionally(&data->ctx);

	LOG_DBG("ADC Initialized");

	return 0;
}

static const struct adc_driver_api api_stm32_driver_api = {
	.channel_setup = adc_stm32_channel_setup,
	.read = adc_stm32_read,
#ifdef CONFIG_ADC_ASYNC
	.read_async = adc_stm32_read_async,
#endif
};

static const struct soc_gpio_pinctrl adc_pins[] = ST_STM32_DT_PINCTRL(adc1, 0);				
									
static const struct adc_ac_stm32_cfg adc_ac_stm32_cfg = {		
	.pinctrl = adc_pins,					
	.pinctrl_len = ARRAY_SIZE(adc_pins),	
	.timer = (TIM_TypeDef *)DT_REG_ADDR(DT_NODELABEL(ADC_TIMER)),					
	.pclken_timer = {							
		.enr = DT_CLOCKS_CELL(DT_NODELABEL(ADC_TIMER), bits),		
		.bus = DT_CLOCKS_CELL(DT_NODELABEL(ADC_TIMER), bus),			
	},								
};			

static struct adc_ac_stm32_data adc_ac_stm32_data = {	
	// .repeat_buffer = adc_repeat_buffer,		
	ADC_CONTEXT_INIT_LOCK(adc_ac_stm32_data, ctx),		
	ADC_CONTEXT_INIT_SYNC(adc_ac_stm32_data, ctx),		
};									
									
DEVICE_DT_DEFINE(DT_NODELABEL(adc1),						
		    &adc_stm32_init, device_pm_control_nop,		
		    &adc_ac_stm32_data, &adc_ac_stm32_cfg,	
		    POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,	
		    &api_stm32_driver_api);				
									
// DT_INST_FOREACH_STATUS_OKAY(STM32_ADC_AC_INIT)
