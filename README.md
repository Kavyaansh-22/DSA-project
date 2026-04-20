# DSA-project

# Hospital Triage & Records Management System

## Overview
This project implements a **Hospital Triage and Records Management System in C**, designed to simulate how patients are prioritized and managed in a clinical environment.

The system focuses on **data structure-driven design**, combining static and dynamic memory techniques to efficiently manage both:
- Real-time patient prioritization
- Permanent patient records

---

## Problem Statement
Manual patient triage in hospitals can lead to delays in treating critical cases.

This project aims to design a **keyword-based automated triage system** that:
- Assigns priority based on symptoms
- Ensures critical patients are treated first
- Maintains a complete record of all admitted patients

---

## Core Features

### 1. Automated Priority Assignment
- Uses **keyword-based string matching (`strstr`)**
- Assigns priority levels:
  - **1 → Critical**
  - **2 → Urgent**
  - **3 → Normal**
- Case-insensitive processing using lowercase normalization

---

### 2. Dynamic Triage Queue
- Implemented using a **Singly Linked List**
- Maintains **sorted order based on priority**
- Ensures:
  - Highest priority patient is always treated first
  - Automatic reordering on insertion

---

### 3. Permanent Patient Records
- Implemented using an **Array of Structures**
- Stores all admitted patients (even after treatment)
- Provides simple and fast historical access

---

### 4. Interactive CLI Interface
Menu-driven system supporting:
- Patient admission
- Treat next patient (dequeue)
- View complete patient history
- View live triage queue

---

## System Design

### Dual Data Structure Approach

| Component              | Data Structure        | Purpose |
|----------------------|----------------------|--------|
| Permanent Records     | Array                | Stores full patient history |
| Live Triage Queue     | Singly Linked List   | Maintains priority ordering |

---

## Working Principle

1. Patient details are entered via CLI
2. Illness description is analyzed using keyword matching
3. Priority is assigned
4. Patient is:
   - Stored in array (history)
   - Inserted into linked list (triage queue)
5. Treatment always removes the **highest priority patient (head of list)**

---

## Time Complexity

| Operation              | Complexity |
|-----------------------|----------|
| Insert (Triage Queue) | O(n)     |
| Treat Patient         | O(1)     |
| Display Records       | O(n)     |

---

## Key Concepts Demonstrated

- Dynamic Memory Allocation (`malloc`, `free`)
- Linked List (Priority Queue behavior)
- Array-based storage
- String processing in C
- Modular programming

---

## Limitations

- Fixed-size array (`MAX_RECORDS`)
- Keyword-based logic (not intelligent classification)
- O(n) insertion in priority queue
- No persistent storage (data resets after execution)

---

## Possible Improvements

- Replace linked list with **heap-based priority queue (O(log n))**
- Implement **file handling for persistent storage**
- Add **timestamp-based tie-breaking**
- Use **NLP/ML-based classification instead of keyword matching**
- Improve input validation and error handling

---

## Conclusion

This project demonstrates how **core data structures can be applied to solve real-world problems** like hospital triage. It highlights the trade-offs between simplicity and efficiency while providing a strong foundation for more advanced system design.

---
