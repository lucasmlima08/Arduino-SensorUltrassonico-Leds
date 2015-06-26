# Arduino: Sensor Ultrassônico com Display LCD e Display de 7 Segmentos.

* Experimento usando Arduino: Um sistema de segurança a partir da distância do alvo, utilizando um sensor ultrassônico 
para receber a distância, um display LCD para dar informações detalhadas e um display de 7 segmentos para informar 
a distância a partir de um parâmetro definido. As informações são enviadas para um banco de dados através de um script 
em python que realiza a leitura a partir da porta serial do arduino. Em seguida as informações são lidas por um 
aplicativo android para que possa ser informado o nível de segurança. O script também envia um email em caso de 
alerta de insegurança.
* O script de leitura da porta serial do arduino e escrita no banco de dados não se encontra nessa pasta do github, 
assim este projeto está contando apenas com o simulador de segurança.

# Circuito
> Neste protótipo foi utilizado um Arduino Mega, mas no projeto foi utilizado um Arduino Uno com uma placa de expansão. As conexões são exatamente iguais.
<img src="https://github.com/lucasmlima08/DispLCD_DispSegmentos_Ultrassonico/blob/master/circuito.jpg" width="500"/>

# Algumas Imagens

<img src="https://github.com/lucasmlima08/Arduino-Ultrassonico-DispLCD-DispSegmentos/blob/master/img_2.jpg" width="450" />
<img src="https://github.com/lucasmlima08/Arduino-Ultrassonico-DispLCD-DispSegmentos/blob/master/img_1.jpg" width="450" />
