#pragma once

#ifdef _WIN32
#include "C:/RedGpuSDK/redgpu.h"
#endif
#ifdef __linux__
#include "/opt/RedGpuSDK/redgpu.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

REDGPU_DECLSPEC void      REDGPU_API rmaVkGetPhysicalDeviceProperties       (RedContext context, unsigned gpuIndex, RedHandleGpuDevice physicalDevice, void * pVkPhysicalDeviceProperties);
REDGPU_DECLSPEC void      REDGPU_API rmaVkGetPhysicalDeviceMemoryProperties (RedContext context, unsigned gpuIndex, RedHandleGpuDevice physicalDevice, void * pVkPhysicalDeviceMemoryProperties);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkAllocateMemory                    (RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkMemoryAllocateInfo, const void * pVkAllocationCallbacks, RedHandleMemory * pMemory);
REDGPU_DECLSPEC void      REDGPU_API rmaVkFreeMemory                        (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory, const void * pVkAllocationCallbacks);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkMapMemory                         (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory, uint64_t offset, uint64_t size, unsigned vkMemoryMapFlags, void ** ppData);
REDGPU_DECLSPEC void      REDGPU_API rmaVkUnmapMemory                       (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkFlushMappedMemoryRanges           (RedContext context, unsigned gpuIndex, RedHandleGpu device, unsigned memoryRangeCount, const void * pVkMappedMemoryRange);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkInvalidateMappedMemoryRanges      (RedContext context, unsigned gpuIndex, RedHandleGpu device, unsigned memoryRangeCount, const void * pVkMappedMemoryRange);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkBindBufferMemory                  (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, RedHandleMemory memory, uint64_t memoryOffset);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkBindImageMemory                   (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, RedHandleMemory memory, uint64_t memoryOffset);
REDGPU_DECLSPEC void      REDGPU_API rmaVkGetBufferMemoryRequirements       (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, void * pVkMemoryRequirements);
REDGPU_DECLSPEC void      REDGPU_API rmaVkGetImageMemoryRequirements        (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, void * pVkMemoryRequirements);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkCreateBuffer                      (RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkBufferCreateInfo, const void * pVkAllocationCallbacks, RedHandleArray * pBuffer);
REDGPU_DECLSPEC void      REDGPU_API rmaVkDestroyBuffer                     (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, const void * pVkAllocationCallbacks);
REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkCreateImage                       (RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkImageCreateInfo, const void * pVkAllocationCallbacks, RedHandleImage * pImage);
REDGPU_DECLSPEC void      REDGPU_API rmaVkDestroyImage                      (RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, const void * pVkAllocationCallbacks);
REDGPU_DECLSPEC void      REDGPU_API rmaVkCmdCopyBuffer                     (RedContext context, unsigned gpuIndex, RedHandleCalls commandBuffer, RedHandleArray srcBuffer, RedHandleArray dstBuffer, unsigned regionCount, const void * pVkBufferCopy);

#ifdef __cplusplus
}
#endif