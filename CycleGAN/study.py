import torch
import torch.nn as nn
import torch.nn.functional as F
import os
import glob

files_A = sorted(glob.glob(os.path.join('datasets/lantingkai/', '%s/A' % 'train') + '/*.*'))
print(files_A)