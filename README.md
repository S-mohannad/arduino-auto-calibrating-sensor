# 🔆 Auto-Calibrating Sensor Threshold with LED Indicator

> **Arduino Project #19** — سنسور يُعاير نفسه تلقائياً ثم يتحكم بـ LED بناءً على threshold محسوب

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Level](https://img.shields.io/badge/Level-Intermediate-orange?style=for-the-badge)](https://github.com/S-mohannad)

---

## 📋 Description

مشروع يقرأ سنسوراً تناظرياً ويُعاير نفسه تلقائياً خلال 8 ثواني:

**مرحلة المعايرة (setup):**
- يصدر buzzer نغمة منخفضة (250Hz) إشارةً لبداية المعايرة
- يقرأ قيم A0 باستمرار لمدة 8 ثواني ويتتبع الـ min والـ max
- يحسب الـ threshold `z` = متوسط (min + max)
- يطبع min و max و z في Serial Monitor
- يصدر buzzer نغمة عالية (950Hz) إشارةً لانتهاء المعايرة

**مرحلة التشغيل (loop):**
- إذا قيمة A0 **أعلى من z** → LED يطفى
- إذا قيمة A0 **أقل من أو تساوي z** → LED يشتغل

---

## 🔌 Circuit

| المكون | التوصيل |
|--------|---------|
| سنسور تناظري | Signal → A0 / VCC → 5V / GND → GND |
| LED | الساق الطويلة → مقاومة 220Ω → pin 7 / الساق القصيرة → GND |
| Buzzer | + → pin 12 / - → GND |

---

## 💡 Concepts Used

- `analogRead()` — قراءة قيمة تناظرية (0–1023) من A0
- `millis()` — قياس الوقت المنقضي لتحديد فترة المعايرة (8 ثواني)
- `max()` و `min()` — تتبع أعلى وأدنى قيمة أثناء المعايرة
- **Auto-calibration** — حساب threshold تلقائياً من بيئة التشغيل
- `tone()` — إصدار نغمة صوتية للإشارة ببداية ونهاية المعايرة
- `digitalWrite()` — التحكم بـ LED بناءً على المقارنة مع الـ threshold

---

## 📊 Behavior

| المرحلة | الحدث |
|---------|-------|
| بداية التشغيل | نغمة 250Hz → بداية المعايرة |
| 0–8 ثواني | قراءة A0 وتتبع min و max |
| بعد 8 ثواني | نغمة 950Hz → طباعة min و max و z |
| loop | LED يشتغل إذا x ≤ z / يطفى إذا x > z |

---

## 🔗 Code

```cpp
int x = 0, z = 0;
int max = 0;
int min = 1023;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  delay(1000);

  tone(12, 250, 100);
  while (millis() < 9000) {
    x = analogRead(A0);
    max = max(max, x);
    min = min(min, x);
  }
  tone(12, 950, 100);

  Serial.print("the min is:  ");
  Serial.print(min);
  Serial.print("   ");
  Serial.print("the max is:  ");
  Serial.println(max);

  z = min + max;
  z = z / 2;
  Serial.print("the z is:  ");
  Serial.print(z);
}

void loop() {
  x = analogRead(A0);
  if (x > z)
    { digitalWrite(7, LOW); }
  else
    { digitalWrite(7, HIGH); }
}
```

---

## 🔧 How to Run

1. افتح **Arduino IDE**
2. وصّل الدائرة (سنسور على A0، LED على pin 7، Buzzer على pin 12)
3. انسخ الكود والصقه في المحرر
4. اختر **Board:** Arduino UNO
5. اختر **Port** الصحيح
6. اضغط ⬆️ **Upload**
7. عند سماع النغمة المنخفضة → حرّك السنسور في نطاق التشغيل الكامل خلال 8 ثواني
8. عند سماع النغمة العالية → انتهت المعايرة، راقب LED يستجيب للسنسور

---

## 👨‍💻 Author

**S-mohannad** — [@S-mohannad](https://github.com/S-mohannad)
