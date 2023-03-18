# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 28.64 | 6.98 mb/s | N/A |
| AES128 Dec | ECB | 200 | 20.90 | 9.57 mb/s | success |
| AES192 Enc | ECB | 200 | 34.03 | 5.88 mb/s | N/A |
| AES192 Dec | ECB | 200 | 24.82 | 8.06 mb/s | success |
| AES256 Enc | ECB | 200 | 39.71 | 5.04 mb/s | N/A |
| AES256 Dec | ECB | 200 | 28.82 | 6.94 mb/s | success |
| AES128 Enc | CBC | 200 | 28.76 | 6.95 mb/s | N/A |
| AES128 Dec | CBC | 200 | 21.12 | 9.47 mb/s | success |
| AES192 Enc | CBC | 200 | 34.45 | 5.81 mb/s | N/A |
| AES192 Dec | CBC | 200 | 25.14 | 7.96 mb/s | success |
| AES256 Enc | CBC | 200 | 40.14 | 4.98 mb/s | N/A |
| AES256 Dec | CBC | 200 | 29.31 | 6.82 mb/s | success |
| AES128 Enc | CFB | 200 | 28.74 | 6.96 mb/s | N/A |
| AES128 Dec | CFB | 200 | 28.62 | 6.99 mb/s | success |
| AES192 Enc | CFB | 200 | 34.39 | 5.82 mb/s | N/A |
| AES192 Dec | CFB | 200 | 34.32 | 5.83 mb/s | success |
| AES256 Enc | CFB | 200 | 40.07 | 4.99 mb/s | N/A |
| AES256 Dec | CFB | 200 | 39.99 | 5.00 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.21 | 164.66 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.36 | 147.02 mb/s | success |
| AES192 Enc | ECB | 200 | 1.31 | 152.87 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.48 | 135.03 mb/s | success |
| AES256 Enc | ECB | 200 | 1.41 | 141.59 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.63 | 122.53 mb/s | success |
| AES128 Enc | CBC | 200 | 1.62 | 123.36 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.71 | 116.98 mb/s | success |
| AES192 Enc | CBC | 200 | 1.71 | 117.13 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.83 | 109.36 mb/s | success |
| AES256 Enc | CBC | 200 | 1.81 | 110.27 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.97 | 101.78 mb/s | success |
| AES128 Enc | CFB | 200 | 1.60 | 125.10 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.51 | 132.53 mb/s | success |
| AES192 Enc | CFB | 200 | 1.70 | 117.83 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.60 | 125.39 mb/s | success |
| AES256 Enc | CFB | 200 | 1.80 | 111.28 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.70 | 117.54 mb/s | success |
