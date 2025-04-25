# ESP-Nexus

ESP-Nexus is a lightweight communication library for the ESP32 platform, designed to unify multiple wireless protocols—currently BLE and ESP-NOW—into a single cohesive messaging layer. Rather than acting as a standalone application or firmware, esp-nexus is meant to be embedded as a component within broader ESP32-based projects, allowing developers to integrate cross-protocol communication without rewriting protocol-specific logic.

At its core, ESP-Nexus abstracts low-level transport details and provides a common interface for sending, receiving, fragmenting, and routing packets across heterogeneous networks. Devices can relay messages even when direct protocol compatibility is unavailable, forming a mesh-of-mesh topology that adapts dynamically to available connections. It supports protocol-aware routing, device health monitoring, and automatic packet reassembly—streamlining communication across diverse hardware setups.

This is an early-stage work in progress, actively being developed and expanded. While the BLE and ESP-NOW backends are functional and integrated, future updates will include support for additional protocols (e.g., LoRa), persistent routing logic, and enhancements to scalability and resilience. 

## Example Use-Cases

- **Low-Power Sensor Clusters**  
  Deep-sleep-optimized ESP32 nodes wake only for brief data bursts, use LoRa for long-range uplink, and BLE/ESP-NOW for nearby configuration—allowing months-to-years of operation on small Li-ion packs or solar-assisted power.

- **Affordable Farm Telemetry**  
  Mid-sized farms deploy soil-moisture and irrigation sensors that forward data through a self-healing mesh, eliminating expensive gateway hardware. Accurate soil data curbs costly over and under watering in small/mid size farms that cannot afford expensive scale systems.

- **Rave / Festival Wearables**  
  LED wearables form per-person BLE meshes that sync color patterns; edge nodes relay show cues over LoRa so your group stays in rhythm - even in congested RF environments.

## Roadmap & TODO


- **LoRa Support**
  - Short-/mid-range P2P mesh (“raw” LoRa)  
  - Operational testing on SX1262 LoRa modules
  - Long-range LoRaWAN (Class A/B/C)  


- **Reliability & Error Recovery**
  - Adaptive, self-healing routing driven by per-link health checks
  - End-to-end route-health scoring and rerouting
  - Packet-delivery confirmations / retransmission
  - Duplicate suppression (seq-nos) and congestion / rate control   ← new
  - TTL / hop-limit to kill routing loops
  - Forward-error-correction for binaries (Forest / Hamming codes, LoRa-focused)

- **Security**
  - Payload encryption (e.g., ChaCha-Poly)
  - Public-key exchange & rotation
  - Per-packet auth tags
  - Signed OTA payloads (secure boot compatible)

- **Device & Network Management**
  - Provisioning workflow (first keys, channels, IDs)
  - Persistent routing cache in predefined flash partitions
  - Metrics + health telemetry
  - Integrated LogAnywhere back-end for remote logging

- **Radio Coordination**
  - BLE / Wi-Fi coexistence scheduler
  - Duty-cycle & sleep-aware routing

- **API**
  - Final API Development and Documentation for use
- **Developer & Ops Tooling**
  - Simulation / CI harness for multi-hop tests   ← new
  - Guides, API reference, worked examples, architecture diagrams
