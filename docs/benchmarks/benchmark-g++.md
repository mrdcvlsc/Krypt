# Benchmark

Compiler : g++

## Pure C++

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 28.23 | 7.09 mb/s | N/A |
| AES128 Dec | ECB | 200 | 20.88 | 9.58 mb/s | success |
| AES192 Enc | ECB | 200 | 33.97 | 5.89 mb/s | N/A |
| AES192 Dec | ECB | 200 | 25.00 | 8.00 mb/s | success |
| AES256 Enc | ECB | 200 | 40.00 | 5.00 mb/s | N/A |
| AES256 Dec | ECB | 200 | 29.39 | 6.80 mb/s | success |
| AES128 Enc | CBC | 200 | 28.30 | 7.07 mb/s | N/A |
| AES128 Dec | CBC | 200 | 21.19 | 9.44 mb/s | success |
| AES192 Enc | CBC | 200 | 33.93 | 5.89 mb/s | N/A |
| AES192 Dec | CBC | 200 | 25.19 | 7.94 mb/s | success |
| AES256 Enc | CBC | 200 | 39.59 | 5.05 mb/s | N/A |
| AES256 Dec | CBC | 200 | 29.29 | 6.83 mb/s | success |
| AES128 Enc | CFB | 200 | 28.62 | 6.99 mb/s | N/A |
| AES128 Dec | CFB | 200 | 28.61 | 6.99 mb/s | success |
| AES192 Enc | CFB | 200 | 34.26 | 5.84 mb/s | N/A |
| AES192 Dec | CFB | 200 | 34.27 | 5.84 mb/s | success |
| AES256 Enc | CFB | 200 | 39.93 | 5.01 mb/s | N/A |
| AES256 Dec | CFB | 200 | 39.97 | 5.00 mb/s | success |

## AES-NI

| Block Cipher | Mode | MB | Seconds | Speed | Result |
| ------------ | ---- | -- | ------- | ----- | ------ |
| AES128 Enc | ECB | 200 | 1.23 | 162.49 mb/s | N/A |
| AES128 Dec | ECB | 200 | 1.24 | 161.83 mb/s | success |
| AES192 Enc | ECB | 200 | 1.33 | 150.22 mb/s | N/A |
| AES192 Dec | ECB | 200 | 1.33 | 150.26 mb/s | success |
| AES256 Enc | ECB | 200 | 1.43 | 140.06 mb/s | N/A |
| AES256 Dec | ECB | 200 | 1.45 | 138.37 mb/s | success |
| AES128 Enc | CBC | 200 | 1.31 | 152.89 mb/s | N/A |
| AES128 Dec | CBC | 200 | 1.45 | 138.34 mb/s | success |
| AES192 Enc | CBC | 200 | 1.41 | 142.33 mb/s | N/A |
| AES192 Dec | CBC | 200 | 1.54 | 129.68 mb/s | success |
| AES256 Enc | CBC | 200 | 1.51 | 132.85 mb/s | N/A |
| AES256 Dec | CBC | 200 | 1.65 | 121.12 mb/s | success |
| AES128 Enc | CFB | 200 | 1.58 | 126.83 mb/s | N/A |
| AES128 Dec | CFB | 200 | 1.43 | 140.31 mb/s | success |
| AES192 Enc | CFB | 200 | 1.67 | 120.08 mb/s | N/A |
| AES192 Dec | CFB | 200 | 1.52 | 131.37 mb/s | success |
| AES256 Enc | CFB | 200 | 1.77 | 112.89 mb/s | N/A |
| AES256 Dec | CFB | 200 | 1.63 | 122.39 mb/s | success |
