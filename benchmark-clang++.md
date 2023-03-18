# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.52 | 12.10 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.49 | 16.02 mb/s | success |
| AES192 Enc | ECB | 200 | 19.78 | 10.11 mb/s | N/A |
| AES192 Dec | ECB | 200 | 14.91 | 13.41 mb/s | success |
| AES256 Enc | ECB | 200 | 23.11 | 8.65 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.34 | 11.53 mb/s | success |
| AES128 Enc | CBC | 200 | 16.92 | 11.82 mb/s | N/A |
| AES128 Dec | CBC | 200 | 12.83 | 15.59 mb/s | success |
| AES192 Enc | CBC | 200 | 20.20 | 9.90 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.27 | 13.10 mb/s | success |
| AES256 Enc | CBC | 200 | 23.40 | 8.55 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.71 | 11.30 mb/s | success |
| AES128 Enc | CFB | 200 | 16.95 | 11.80 mb/s | N/A |
| AES128 Dec | CFB | 200 | 16.81 | 11.90 mb/s | success |
| AES192 Enc | CFB | 200 | 20.20 | 9.90 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.05 | 9.97 mb/s | success |
| AES256 Enc | CFB | 200 | 23.45 | 8.53 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.30 | 8.59 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.32 | 151.77 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.50 | 133.47 mb/s | success |
| AES192 Enc | ECB | 200 | 1.41 | 142.03 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.60 | 125.15 mb/s | success |
| AES256 Enc | ECB | 200 | 1.51 | 132.71 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.71 | 117.29 mb/s | success |
| AES128 Enc | CBC | 200 | 1.75 | 113.99 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.84 | 108.72 mb/s | success |
| AES192 Enc | CBC | 200 | 1.84 | 108.50 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.98 | 101.16 mb/s | success |
| AES256 Enc | CBC | 200 | 1.95 | 102.82 mb/s | N/A |
| AES256 Dec | CBC | 200 | 2.11 | 94.68 mb/s | success |
| AES128 Enc | CFB | 200 | 1.78 | 112.46 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.62 | 123.11 mb/s | success |
| AES192 Enc | CFB | 200 | 1.88 | 106.59 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.73 | 115.44 mb/s | success |
| AES256 Enc | CFB | 200 | 1.96 | 101.84 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.85 | 108.32 mb/s | success |
