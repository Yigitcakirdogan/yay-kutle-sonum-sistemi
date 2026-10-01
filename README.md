# Yay-Kütle-Sönüm Sistemi

Lineer zamanla değişmeyen bir yay-kütle-sönüm sisteminin sonlu farklar yöntemi kullanılarak Python ile simülasyonu.

## Sistem Modeli

Sistemin diferansiyel denklemi:

mẍ + cẋ + kx = F(t)

Kullanılan sistem parametreleri:

- Kütle: 1 kg
- Sönüm katsayısı: 0.5 N·s/m
- Yay sabiti: 10 N/m
- Dış kuvvet: 1 N
- Zaman adımı: 0.01 s
- Simülasyon süresi: 5 s

## Yöntem

Sistem durum değişkenleri kullanılarak modellenmiş ve sonlu farklar yöntemi ile sayısal olarak çözülmüştür.

Hız:

v[n] = v[n-1] + Δt · a[n-1]

Konum:

x[n] = x[n-1] + Δt · v[n-1]

## Kullanılan Teknolojiler

- Python 3.13
- NumPy
- Tkinter

## Çalıştırma

Gerekli paketleri yükleyin:

pip install -r requirements.txt

Ardından:

python yay_simulasyon.py

## Proje

Bu çalışma, dinamik sistemlerin sonlu farklar yöntemi ile sayısal simülasyonunu gerçekleştirmek amacıyla hazırlanmıştır.
