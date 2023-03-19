# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.53 | 12.10 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.47 | 16.04 mb/s | success |
| AES192 Enc | ECB | 200 | 19.76 | 10.12 mb/s | N/A |
| AES192 Dec | ECB | 200 | 14.90 | 13.42 mb/s | success |
| AES256 Enc | ECB | 200 | 23.09 | 8.66 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.33 | 11.54 mb/s | success |
| AES128 Enc | CBC | 200 | 16.90 | 11.84 mb/s | N/A |
| AES128 Dec | CBC | 200 | 12.79 | 15.64 mb/s | success |
| AES192 Enc | CBC | 200 | 20.15 | 9.93 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.23 | 13.13 mb/s | success |
| AES256 Enc | CBC | 200 | 23.37 | 8.56 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.66 | 11.33 mb/s | success |
| AES128 Enc | CFB | 200 | 16.94 | 11.80 mb/s | N/A |
| AES128 Dec | CFB | 200 | 16.78 | 11.92 mb/s | success |
| AES192 Enc | CFB | 200 | 20.18 | 9.91 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.04 | 9.98 mb/s | success |
| AES256 Enc | CFB | 200 | 23.41 | 8.54 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.25 | 8.60 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.26 | 158.31 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.31 | 152.69 mb/s | success |
| AES192 Enc | ECB | 200 | 1.36 | 147.02 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.42 | 140.90 mb/s | success |
| AES256 Enc | ECB | 200 | 1.46 | 137.39 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.53 | 130.51 mb/s | success |
| AES128 Enc | CBC | 200 | 1.71 | 116.70 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.71 | 117.13 mb/s | success |
| AES192 Enc | CBC | 200 | 1.81 | 110.70 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.82 | 109.88 mb/s | success |
| AES256 Enc | CBC | 200 | 1.89 | 105.57 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.92 | 103.95 mb/s | success |
| AES128 Enc | CFB | 200 | 1.73 | 115.77 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.60 | 124.90 mb/s | success |
| AES192 Enc | CFB | 200 | 1.82 | 109.60 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.69 | 118.07 mb/s | success |
| AES256 Enc | CFB | 200 | 1.91 | 104.72 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.78 | 112.05 mb/s | success |
