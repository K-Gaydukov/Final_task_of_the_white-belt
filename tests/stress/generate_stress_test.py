import random
import datetime

def generate_random_date():
    year = random.randint(-100, 2025)
    month = random.randint(1, 12)
    day = random.randint(1, 28)  # Простое ограничение для валидных дат
    return f"{year:04d}-{month:02d}-{day:02d}"

def generate_random_event():
    events = ["Meeting", "Task", "Reminder", "Event" + str(random.randint(1, 100))]
    return random.choice(events)

def generate_stress_test(num_commands=100):
    commands = []
    for _ in range(num_commands):
        cmd_type = random.choice(["Add", "Del", "Find", "Print"])
        if cmd_type == "Print":
            commands.append("Print")
        elif cmd_type == "Find":
            commands.append(f"Find {generate_random_date()}")
        elif cmd_type == "Add":
            commands.append(f"Add {generate_random_date()} {generate_random_event()}")
        elif cmd_type == "Del":
            if random.random() < 0.5:
                commands.append(f"Del {generate_random_date()}")
            else:
                commands.append(f"Del {generate_random_date()} {generate_random_event()}")
    return commands

if __name__ == "__main__":
    for cmd in generate_stress_test(100):
        print(cmd)