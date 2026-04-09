# DSA-project

Hospital Triage & Records Management System
A high-performance Hospital Management System implemented in C, designed to automate patient prioritization and maintain historical medical records. This project demonstrates the practical use of dynamic memory management and prioritized data organization.

Problem Statement
To design an automated Hospital Triage System in C that replaces manual patient sorting with a real-time, keyword-based priority management engine, ensuring critical cases receive immediate medical attention.

Key Features
Automated Priority Calculation: Analyzes patient symptoms (illness description) to assign a priority level (1: Critical, 2: Urgent, 3: Normal).

Real-Time Triage: A live waiting list that automatically re-orders itself whenever a new patient arrives based on medical severity.

Historical Logging: Maintains a permanent, session-long record of every patient admitted using static storage.

Interactive Menu: A user-friendly CLI to admit patients, treat the next available person, and view records.

Methodology & Data StructuresThis system utilizes a dual-layer data management approach:
Array of Structures (Permanent Database): Used to store the PatientRecord history. This ensures that even after a patient is "treated" and removed from the queue, their data remains accessible for administrative review (Ref: Lab Experiment 4).
Singly Linked List (Live Triage Queue): Used for the active waiting list. It employs Priority Queue logic where nodes are inserted in a sorted manner  to ensure the highest priority patient is always at the "Head" for  retrieval (Ref: Lab Experiment 6 & 10).Keyword-Based Logic: Uses string parsing (strstr) and case normalization to detect life-threatening symptoms and adjust the queue dynamically.
