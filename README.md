# STM8L051

最近花了两周时间，研究了下STM8L051；
主要包括I2C slave通信, UART通信，ADC电压采集，GPIO按键，低功耗模式；

其中I2C和UART通信中，设计了RingBuffer做数据缓冲；

代码虽少，但采用模块化结构，更清晰明了；
