# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.79 | 11.91 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.60 | 15.88 mb/s | success |
| AES192 Enc | ECB | 200 | 20.06 | 9.97 mb/s | N/A |
| AES192 Dec | ECB | 200 | 15.05 | 13.29 mb/s | success |
| AES256 Enc | ECB | 200 | 23.40 | 8.55 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.51 | 11.43 mb/s | success |
| AES128 Enc | CBC | 200 | 17.01 | 11.75 mb/s | N/A |
| AES128 Dec | CBC | 200 | 13.00 | 15.39 mb/s | success |
| AES192 Enc | CBC | 200 | 20.29 | 9.86 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.45 | 12.95 mb/s | success |
| AES256 Enc | CBC | 200 | 23.64 | 8.46 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.91 | 11.17 mb/s | success |
| AES128 Enc | CFB | 200 | 17.20 | 11.63 mb/s | N/A |
| AES128 Dec | CFB | 200 | 17.01 | 11.76 mb/s | success |
| AES192 Enc | CFB | 200 | 20.46 | 9.77 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.27 | 9.87 mb/s | success |
| AES256 Enc | CFB | 200 | 23.82 | 8.40 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.55 | 8.49 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.32 | 151.00 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.20 | 167.25 mb/s | success |
| AES192 Enc | ECB | 200 | 1.42 | 141.23 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.35 | 148.57 mb/s | success |
| AES256 Enc | ECB | 200 | 1.45 | 137.54 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.41 | 141.37 mb/s | success |
| AES128 Enc | CBC | 200 | 1.59 | 125.64 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.71 | 116.85 mb/s | success |
| AES192 Enc | CBC | 200 | 1.67 | 119.77 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.83 | 109.06 mb/s | success |
| AES256 Enc | CBC | 200 | 1.79 | 111.56 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.92 | 104.22 mb/s | success |
| AES128 Enc | CFB | 200 | 1.75 | 114.29 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.55 | 128.66 mb/s | success |
| AES192 Enc | CFB | 200 | 1.89 | 106.04 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.70 | 117.95 mb/s | success |
| AES256 Enc | CFB | 200 | 1.93 | 103.59 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.76 | 113.55 mb/s | success |
