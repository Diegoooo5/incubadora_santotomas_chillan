# incubadora_santotomas_chillan
proyecto incubadora 

📌 1. Conexiones del DHT22
	•	VCC (DHT22) → 5V en Arduino
	•	GND (DHT22) → GND en Arduino
	•	DATA (DHT22) → Pin digital 2 en Arduino
	•	⚠️ Importante: colocar una resistencia de 10kΩ entre DATA y VCC como pull-up.

⸻

📌 2. Conexiones del LCD 1602A (con módulo I2C)
	•	VCC (LCD) → 5V en Arduino
	•	GND (LCD) → GND en Arduino
	•	SDA (LCD) → A4 en Arduino UNO
	•	SCL (LCD) → A5 en Arduino UNO

(Si usas un Arduino Mega, SDA va al pin 20 y SCL al pin 21)

⸻

📌 3. Conexiones del Módulo Relé
	•	VCC (Relé) → 5V en Arduino
	•	GND (Relé) → GND en Arduino
	•	IN (Relé) → Pin digital 8 en Arduino

⸻

📌 4. Conexión del Foco (220V o 110V AC)

👉 Mucho cuidado ⚠️, aquí trabajas con voltaje de red, usa aislación y no toques los cables energizados.
	•	El relé funciona como interruptor:
	•	COM (común del relé) → un cable de la red eléctrica (fase).
	•	NO (normalmente abierto del relé) → va al foco.
	•	El otro cable del foco → directo al neutro de la red.

De esta forma, cuando el Arduino activa el relé, el contacto se cierra y el foco se enciende.
