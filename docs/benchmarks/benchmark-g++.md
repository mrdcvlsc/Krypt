# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 28.72 | 6.96 mb/s | N/A |
| AES128 Dec | ECB | 200 | 21.16 | 9.45 mb/s | success |
| AES192 Enc | ECB | 200 | 34.12 | 5.86 mb/s | N/A |
| AES192 Dec | ECB | 200 | 24.84 | 8.05 mb/s | success |
| AES256 Enc | ECB | 200 | 39.97 | 5.00 mb/s | N/A |
| AES256 Dec | ECB | 200 | 29.35 | 6.81 mb/s | success |
| AES128 Enc | CBC | 200 | 29.27 | 6.83 mb/s | N/A |
| AES128 Dec | CBC | 200 | 21.60 | 9.26 mb/s | success |
| AES192 Enc | CBC | 200 | 34.90 | 5.73 mb/s | N/A |
| AES192 Dec | CBC | 200 | 25.44 | 7.86 mb/s | success |
| AES256 Enc | CBC | 200 | 40.82 | 4.90 mb/s | N/A |
| AES256 Dec | CBC | 200 | 29.38 | 6.81 mb/s | success |
| AES128 Enc | CFB | 200 | 28.83 | 6.94 mb/s | N/A |
| AES128 Dec | CFB | 200 | 29.00 | 6.90 mb/s | success |
| AES192 Enc | CFB | 200 | 34.79 | 5.75 mb/s | N/A |
| AES192 Dec | CFB | 200 | 34.62 | 5.78 mb/s | success |
| AES256 Enc | CFB | 200 | 40.53 | 4.93 mb/s | N/A |
| AES256 Dec | CFB | 200 | 40.82 | 4.90 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.24 | 161.66 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.39 | 143.85 mb/s | success |
| AES192 Enc | ECB | 200 | 1.36 | 146.96 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.55 | 129.38 mb/s | success |
| AES256 Enc | ECB | 200 | 1.47 | 136.50 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.68 | 119.19 mb/s | success |
| AES128 Enc | CBC | 200 | 1.67 | 119.56 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.74 | 115.09 mb/s | success |
| AES192 Enc | CBC | 200 | 1.73 | 115.33 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.86 | 107.26 mb/s | success |
| AES256 Enc | CBC | 200 | 1.86 | 107.68 mb/s | N/A |
| AES256 Dec | CBC | 200 | 2.00 | 100.01 mb/s | success |
| AES128 Enc | CFB | 200 | 1.64 | 121.94 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.54 | 129.61 mb/s | success |
| AES192 Enc | CFB | 200 | 1.74 | 115.13 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.62 | 123.21 mb/s | success |
| AES256 Enc | CFB | 200 | 1.82 | 109.67 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.74 | 115.21 mb/s | success |
