import numpy as np
import tkinter as tk

# ==========================================
# 1. SİSTEM PARAMETRELERİ
# ==========================================

m = 1.0       # Kütle (kg)
c = 0.5       # Sönüm katsayısı (N.s/m)
k = 10.0      # Yay sabiti (N/m)

dt = 0.01     # Zaman adımı (s)
T = 5.0       # Toplam simülasyon süresi (s)

# Zaman dizisi
t = np.arange(0, T + dt, dt)
N = len(t)

# ==========================================
# 2. BAŞLANGIÇ KOŞULLARI
# ==========================================

x = np.zeros(N)       # Konum
v = np.zeros(N)       # Hız
a = np.zeros(N)       # İvme

x[0] = 0.0            # Başlangıç konumu (m)
v[0] = 0.0            # Başlangıç hızı (m/s)

# Sabit dış kuvvet
def F(t):
    return 1.0        # 1 Newton

# Başlangıç ivmesi
a[0] = (F(t[0]) - c * v[0] - k * x[0]) / m

# ==========================================
# 3. SONLU FARKLAR YÖNTEMİ
# ==========================================

for n in range(1, N):

    # İvme
    a[n-1] = (
        F(t[n-1])
        - c * v[n-1]
        - k * x[n-1]
    ) / m

    # Hız
    v[n] = v[n-1] + dt * a[n-1]

    # Konum
    x[n] = x[n-1] + dt * v[n-1]

# Son noktadaki ivme
a[-1] = (F(t[-1]) - c * v[-1] - k * x[-1]) / m

# ==========================================
# 4. SONUÇLARI EKRANA YAZDIR
# ==========================================

print("Simülasyon tamamlandı.")
print("-----------------------")
print(f"Başlangıç konumu : {x[0]:.4f} m")
print(f"Son konum        : {x[-1]:.4f} m")
print(f"Son hız          : {v[-1]:.4f} m/s")
print(f"Son ivme         : {a[-1]:.4f} m/s²")
print(f"Adım sayısı      : {N}")

# ==========================================
# 5. TKINTER İLE GRAFİK
# ==========================================

pencere = tk.Tk()
pencere.title("Yay-Kütle-Sönüm Sistemi - Sonlu Farklar")
pencere.geometry("1000x600")

canvas = tk.Canvas(
    pencere,
    width=950,
    height=500,
    bg="white"
)

canvas.pack(pady=30)

# Grafik sınırları
sol = 70
sag = 920
ust = 40
alt = 450

# Eksenler
canvas.create_line(sol, alt, sag, alt, width=2)
canvas.create_line(sol, ust, sol, alt, width=2)

# Başlık
canvas.create_text(
    475,
    15,
    text="Konum - Zaman Grafiği",
    font=("Arial", 16)
)

canvas.create_text(
    475,
    480,
    text="Zaman (s)",
    font=("Arial", 12)
)

canvas.create_text(
    20,
    250,
    text="Konum (m)",
    angle=90,
    font=("Arial", 12)
)

# Grafik için ölçek
x_min = np.min(x)
x_max = np.max(x)

if x_max == x_min:
    x_max = x_min + 1

# Biraz boşluk bırak
bosluk = 0.1 * (x_max - x_min)
x_min -= bosluk
x_max += bosluk

# Grafik noktalarını çiz
for i in range(N - 1):

    px1 = sol + (t[i] / T) * (sag - sol)
    px2 = sol + (t[i+1] / T) * (sag - sol)

    py1 = alt - ((x[i] - x_min) / (x_max - x_min)) * (alt - ust)
    py2 = alt - ((x[i+1] - x_min) / (x_max - x_min)) * (alt - ust)

    canvas.create_line(
        px1, py1,
        px2, py2,
        width=2
    )

# Pencereyi açık tut
pencere.mainloop()