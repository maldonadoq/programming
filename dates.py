import csv
from datetime import datetime, timedelta

# Fecha inicial
start_date = datetime(2025, 8, 25)

# (0=Lunes, 1=Martes, ..., 6=Domingo)
target_days = [2,3,4]

fechas = []
for semana in range(17):
    base_date = start_date + timedelta(weeks=semana)
    for d in target_days:
        diff = (d - base_date.weekday()) % 7
        fecha_obj = base_date + timedelta(days=diff)
        fechas.append(fecha_obj.strftime("%d/%m"))

with open("dates.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(fechas)