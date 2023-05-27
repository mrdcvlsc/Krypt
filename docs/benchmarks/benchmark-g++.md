# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 128 | 16.91 | 7.57 mb/s | N/A |
| AES128 Dec | ECB | 128 | 13.76 | 9.30 mb/s | success |
| AES192 Enc | ECB | 128 | 20.23 | 6.33 mb/s | N/A |
| AES192 Dec | ECB | 128 | 16.43 | 7.79 mb/s | success |
| AES256 Enc | ECB | 128 | 23.57 | 5.43 mb/s | N/A |
| AES256 Dec | ECB | 128 | 19.10 | 6.70 mb/s | success |
| AES128 Enc | CBC | 128 | 16.87 | 7.59 mb/s | N/A |
| AES128 Dec | CBC | 128 | 13.92 | 9.20 mb/s | success |
| AES192 Enc | CBC | 128 | 20.22 | 6.33 mb/s | N/A |
| AES192 Dec | CBC | 128 | 16.59 | 7.72 mb/s | success |
| AES256 Enc | CBC | 128 | 23.56 | 5.43 mb/s | N/A |
| AES256 Dec | CBC | 128 | 19.26 | 6.65 mb/s | success |
| AES128 Enc | CFB | 128 | 17.08 | 7.50 mb/s | N/A |
| AES128 Dec | CFB | 128 | 17.00 | 7.53 mb/s | success |
| AES192 Enc | CFB | 128 | 20.41 | 6.27 mb/s | N/A |
| AES192 Dec | CFB | 128 | 20.33 | 6.30 mb/s | success |
| AES256 Enc | CFB | 128 | 23.75 | 5.39 mb/s | N/A |
| AES256 Dec | CFB | 128 | 23.66 | 5.41 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 128 | 0.79 | 162.03 mb/s | N/A |
| AES128 Dec | ECB | 128 | 0.79 | 161.53 mb/s | success |
| AES192 Enc | ECB | 128 | 0.85 | 150.63 mb/s | N/A |
| AES192 Dec | ECB | 128 | 0.85 | 149.90 mb/s | success |
| AES256 Enc | ECB | 128 | 0.91 | 140.16 mb/s | N/A |
| AES256 Dec | ECB | 128 | 0.92 | 139.49 mb/s | success |
| AES128 Enc | CBC | 128 | 0.84 | 152.70 mb/s | N/A |
| AES128 Dec | CBC | 128 | 0.93 | 138.11 mb/s | success |
| AES192 Enc | CBC | 128 | 0.90 | 142.18 mb/s | N/A |
| AES192 Dec | CBC | 128 | 0.99 | 129.42 mb/s | success |
| AES256 Enc | CBC | 128 | 0.96 | 132.82 mb/s | N/A |
| AES256 Dec | CBC | 128 | 1.05 | 121.72 mb/s | success |
| AES128 Enc | CFB | 128 | 1.01 | 126.82 mb/s | N/A |
| AES128 Dec | CFB | 128 | 0.91 | 140.21 mb/s | success |
| AES192 Enc | CFB | 128 | 1.07 | 119.91 mb/s | N/A |
| AES192 Dec | CFB | 128 | 0.98 | 131.20 mb/s | success |
| AES256 Enc | CFB | 128 | 1.14 | 112.50 mb/s | N/A |
| AES256 Dec | CFB | 128 | 1.04 | 123.16 mb/s | success |
