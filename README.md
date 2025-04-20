# Network Scanning GUI

A simple Windows GUI application for scanning network ports, built with Win32 API. This project is in it's early stages.

## Features
- Scan any IP address and port combination
- Detects open/closed/filtered ports
- Uses error correcting to determine port status (soon will change after npcap implementation)
- Resolves hostnames for scanned IPs
- Clean Win32 interface with ESC key to exit

## Requirements
- Windows OS
- GCC (MinGW) for compilation
- Winsock2 (included with Windows)

## Expectations and Future Updates
- Range IP/Port inputs
- Deeper packet inspection with npcap
- UDP and other TCP type scans