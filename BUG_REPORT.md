# Bug Report: Medcouple Implementation Issues

## Summary

The `medcouple()` function in robustats has critical bugs that cause:
1. **NaN returns** for arrays with many repeated values
2. **Incorrect results** even for documented examples
3. **Out-of-bounds memory access** due to missing bounds checks

## Environment

- robustats version: 0.1.7
- NumPy version: 2.3.4
- Python version: 3.13.6
- OS: Linux

## Bug Description

The medcouple C implementation has unbounded while loops that can access memory out of bounds when processing arrays with repeated median values.

### Problematic Code (c/robustats.c)

**Lines 196-200:**
```c
while(lowest_median == median)
{
    lowest_median_index++;
    lowest_median = x[lowest_median_index];  // ⚠️ NO BOUNDS CHECK
}
```

**Lines 210-214:**
```c
while(highest_median == median)
{
    highest_median_index--;
    highest_median = x[highest_median_index];  // ⚠️ CAN GO NEGATIVE
}
```

These loops assume there are non-median values, but fail when:
- Most/all values equal the median
- The median appears at array boundaries

## Reproduction

### Test Cases

```python
import numpy as np
from robustats import medcouple as rbt_medcouple
from statsmodels.stats.stattools import medcouple as stms_medcouple

test_cases = [
    ([0, 1, 2, 2, 3], "Multiple median values"),
    ([1, 2, 2, 2, 3, 4], "Many median values"),
    ([1, 2, 2, 2, 2, 3, 4], "Majority median values"),
    ([0.2, 0.17, 0.08, 0.16, 0.88, 0.86, 0.09, 0.54, 0.27, 0.14], "README example"),
    ([1]*10 + [5]*3, "Skewed distribution"),
    ([10.0]*480 + list(range(1, 21)), "Heavily repeated values"),
    (list(np.random.poisson(1, size=500)), "Poisson distribution"),
]

print("Test Results:")
print("-" * 80)
for arr, description in test_cases:
    x = np.array(arr, dtype=np.float64)
    rbt_result = rbt_medcouple(x)
    stms_result = stms_medcouple(x)

    status = "❌ NaN" if np.isnan(rbt_result) else (
        "❌ WRONG" if abs(rbt_result - stms_result) > 1e-6 else "✅ OK"
    )

    print(f"{status} {description}")
    print(f"   robustats:   {rbt_result:.6f}")
    print(f"   statsmodels: {stms_result:.6f}")
    print()
```

### Actual Output

```
❌ NaN Multiple median values
   robustats:   nan
   statsmodels: -0.166667

❌ WRONG Many median values
   robustats:   1.000000
   statsmodels: 0.166667

❌ NaN Majority median values
   robustats:   nan
   statsmodels: 0.166667

❌ WRONG README example
   robustats:   0.775000
   statsmodels: 0.730769

✅ OK Skewed distribution
   robustats:   1.000000
   statsmodels: 1.000000

❌ NaN Heavily repeated values
   robustats:   nan
   statsmodels: 0.026316
```

## Impact

- **Data Corruption**: Silent failures (NaN) can propagate through analysis pipelines
- **Incorrect Statistical Inference**: Wrong medcouple values lead to incorrect skewness assessments
- **Production Risk**: Unsuitable for production use with real-world data containing duplicates

## Expected Behavior

The function should:
1. Handle arrays with repeated values correctly
2. Match statsmodels results (the reference implementation)
3. Never return NaN for valid input
4. Match its own documented examples

## Suggested Fix

Add bounds checking to the while loops:

```c
// Line 196-200 fix:
while(lowest_median_index < n - 1 && lowest_median == median)
{
    lowest_median_index++;
    lowest_median = x[lowest_median_index];
}

// Line 210-214 fix:
while(highest_median_index > 0 && highest_median == median)
{
    highest_median_index--;
    highest_median = x[highest_median_index];
}
```

However, this is a **minimal fix** and may not address the algorithmic correctness issues causing wrong results even when not returning NaN.

## Comparison with statsmodels

Statsmodels' medcouple implementation:
- Handles all edge cases correctly
- Matches published algorithm specifications
- Has comprehensive test coverage
- Is actively maintained

## Recommendation

Until these bugs are fixed, **use statsmodels** for medcouple calculations:

```python
from statsmodels.stats.stattools import medcouple
```

## References

1. Original Paper: Brys, G., Hubert, M., & Struyf, A. (2004). "A Robust Measure of Skewness". Journal of Computational and Graphical Statistics, 13(4), 996-1017.
2. Statsmodels implementation: https://github.com/statsmodels/statsmodels
3. Test comparison gist: [Include link to your comparison if published]

---

**Note**: This issue affects production use and should be considered **critical priority**.