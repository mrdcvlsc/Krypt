# Benchmark

Compiler : clang++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 16.74 | 11.95 mb/s | N/A |
| AES128 Dec | ECB | 200 | 12.60 | 15.88 mb/s | success |
| AES192 Enc | ECB | 200 | 20.31 | 9.85 mb/s | N/A |
| AES192 Dec | ECB | 200 | 15.12 | 13.23 mb/s | success |
| AES256 Enc | ECB | 200 | 23.35 | 8.56 mb/s | N/A |
| AES256 Dec | ECB | 200 | 17.38 | 11.51 mb/s | success |
| AES128 Enc | CBC | 200 | 17.22 | 11.62 mb/s | N/A |
| AES128 Dec | CBC | 200 | 12.94 | 15.46 mb/s | success |
| AES192 Enc | CBC | 200 | 20.43 | 9.79 mb/s | N/A |
| AES192 Dec | CBC | 200 | 15.44 | 12.95 mb/s | success |
| AES256 Enc | CBC | 200 | 23.70 | 8.44 mb/s | N/A |
| AES256 Dec | CBC | 200 | 17.94 | 11.15 mb/s | success |
| AES128 Enc | CFB | 200 | 17.16 | 11.66 mb/s | N/A |
| AES128 Dec | CFB | 200 | 17.14 | 11.67 mb/s | success |
| AES192 Enc | CFB | 200 | 20.49 | 9.76 mb/s | N/A |
| AES192 Dec | CFB | 200 | 20.30 | 9.85 mb/s | success |
| AES256 Enc | CFB | 200 | 23.69 | 8.44 mb/s | N/A |
| AES256 Dec | CFB | 200 | 23.49 | 8.51 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.37 | 146.51 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.31 | 152.90 mb/s | success |
| AES192 Enc | ECB | 200 | 1.37 | 146.06 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.42 | 140.36 mb/s | success |
| AES256 Enc | ECB | 200 | 1.50 | 133.08 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.54 | 130.28 mb/s | success |
| AES128 Enc | CBC | 200 | 1.74 | 115.16 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.70 | 117.47 mb/s | success |
| AES192 Enc | CBC | 200 | 1.81 | 110.25 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.85 | 108.39 mb/s | success |
| AES256 Enc | CBC | 200 | 1.90 | 105.34 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.92 | 103.97 mb/s | success |
| AES128 Enc | CFB | 200 | 1.73 | 115.66 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.60 | 124.84 mb/s | success |
| AES192 Enc | CFB | 200 | 1.83 | 109.32 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.69 | 118.02 mb/s | success |
| AES256 Enc | CFB | 200 | 1.92 | 104.16 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.78 | 112.59 mb/s | success |
