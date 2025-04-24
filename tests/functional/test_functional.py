import subprocess
import os

def run_database(input_data):
    process = subprocess.run(
        ["../../build/DateBase"],
        input=input_data,
        text=True,
        capture_output=True
    )
    return process.stdout

def test_basic_operations():
    input_data = """Add 2023-01-01 event1
Add 2023-01-01 event2
Find 2023-01-01
Print
"""
    expected_output = """event1
event2
2023-01-01 event1
2023-01-01 event2
"""
    assert run_database(input_data) == expected_output

def test_duplicate_event():
    input_data = """Add 2023-01-01 event1
Add 2023-01-01 event1
Find 2023-01-01
"""
    expected_output = """event1
"""
    assert run_database(input_data) == expected_output

def test_delete_event():
    input_data = """Add 2023-01-01 event1
Del 2023-01-01 event1
Find 2023-01-01
"""
    expected_output = """Deleted successfully
"""
    assert run_database(input_data) == expected_output

def test_delete_all_events():
    input_data = """Add 2023-01-01 event1
Add 2023-01-01 event2
Del 2023-01-01
Print
"""
    expected_output = """Deleted 2 events
"""
    assert run_database(input_data) == expected_output

def test_invalid_date():
    input_data = """Add 2023-13-01 event1
Print
"""
    expected_output = """Month value is invalid: 13
"""
    assert run_database(input_data) == expected_output

def test_invalid_command():
    input_data = """Invalid 2023-01-01
Print
"""
    expected_output = """Unknown command: Invalid
"""
    assert run_database(input_data) == expected_output

def test_negative_date():
    input_data = """Add -1-12-31 event1
Find -1-12-31
"""
    expected_output = """event1
"""
    assert run_database(input_data) == expected_output