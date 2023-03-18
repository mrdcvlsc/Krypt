# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.54 | 12.09 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.47 | 16.04 mb/s | success |
| AES192 Enc | ECB | 200 | 19.79 | 10.10 mb/s | N/A |
| AES192 Dec | ECB | 200 | 14.91 | 13.41 mb/s | success |
| AES256 Enc | ECB | 200 | 23.12 | 8.65 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.35 | 11.53 mb/s | success |
| AES128 Enc | CBC | 200 | 16.95 | 11.80 mb/s | N/A |
| AES128 Dec | CBC | 200 | 12.81 | 15.62 mb/s | success |
| AES192 Enc | CBC | 200 | 20.21 | 9.89 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.25 | 13.12 mb/s | success |
| AES256 Enc | CBC | 200 | 23.42 | 8.54 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.68 | 11.31 mb/s | success |
| AES128 Enc | CFB | 200 | 16.97 | 11.78 mb/s | N/A |
| AES128 Dec | CFB | 200 | 16.80 | 11.91 mb/s | success |
| AES192 Enc | CFB | 200 | 20.21 | 9.89 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.04 | 9.98 mb/s | success |
| AES256 Enc | CFB | 200 | 23.47 | 8.52 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.27 | 8.60 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.28 | 155.75 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.47 | 136.47 mb/s | success |
| AES192 Enc | ECB | 200 | 1.41 | 142.15 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.60 | 125.09 mb/s | success |
| AES256 Enc | ECB | 200 | 1.51 | 132.71 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.72 | 116.49 mb/s | success |
| AES128 Enc | CBC | 200 | 1.83 | 109.41 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.82 | 109.74 mb/s | success |
| AES192 Enc | CBC | 200 | 1.85 | 108.13 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.96 | 101.93 mb/s | success |
| AES256 Enc | CBC | 200 | 1.95 | 102.33 mb/s | N/A |
| AES256 Dec | CBC | 200 | 2.05 | 97.36 mb/s | success |
| AES128 Enc | CFB | 200 | 1.82 | 110.13 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.62 | 123.08 mb/s | success |
| AES192 Enc | CFB | 200 | 1.87 | 106.95 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.71 | 116.65 mb/s | success |
| AES256 Enc | CFB | 200 | 1.97 | 101.77 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.81 | 110.25 mb/s | success |
