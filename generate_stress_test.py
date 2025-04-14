dates = [f"2023-{str(i).zfill(2)}-01" for i in range(1, 11)]
events = [f"Event{i}" for i in range(1, 101)]

with open("stress_test.txt", "w") as f:
    for date in dates:
        for event in events:
            f.write(f"Add {date} {event}\n")
    f.write(f"Find 2023-01-01\n")
    f.write(f"Del 2023-02-01\n")
    f.write(f"Print\n")