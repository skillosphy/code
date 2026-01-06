from time import time
import numpy as np
from numba import cuda
import math

@cuda.jit
def simulate_kernel(results, N):
    tid = cuda.grid(1)
    if tid >= N:
        return
    
    good = 0
    curr = [0, 0, 1, 1, 1, 1]  # 1-based indexing
    state = tid * 17 + 12345  # simple seed per thread
    
    for step in range(2, 16):
        # find available
        avail = []
        for i in range(1, 6):
            if curr[i]:
                avail.append(i)
        if len(avail) == 1:
            good += 1
        # pseudo-random choice
        state = (1103515245 * state + 12345) & 0x7fffffff
        val = avail[state % len(avail)]
        curr[val] -= 1
        if val < 5:
            for i in range(val + 1, 6):
                curr[i] += 1
    
    results[tid] = good

def simulation_gpu(N=10**7):  # adjust based on GPU memory
    threads_per_block = 256
    blocks = math.ceil(N / threads_per_block)
    
    results = np.zeros(N, dtype=np.int32)
    d_results = cuda.to_device(results)
    
    simulate_kernel[blocks, threads_per_block](d_results, N)
    d_results.copy_to_host(results)
    
    return results.sum() / (N * 14)

if __name__ == "__main__":
    start_time = time()
    ans = simulation_gpu()
    print(ans)
    print("Time:", time() - start_time)
