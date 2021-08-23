#include "redgpu_memory_allocator_functions.h"

#define VK_NO_PROTOTYPES
#ifdef _WIN32
#include "C:/VulkanSDK/1.2.135.0/Include/vulkan/vulkan.h"
#endif
#ifdef __linux__
#include "/opt/RedGpuSDK/sdk/1.2.135.0/x86_64/include/vulkan/vulkan.h"
#endif

#include <mutex> // For mutex
#include <map>   // For map

std::mutex                         __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArraysMutex;
std::map<RedHandleArray, RedArray> __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArrays;
std::mutex                         __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImagesMutex;
std::map<RedHandleImage, RedImage> __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImages;

typedef struct RmaPhysicalDeviceLimits {
  unsigned  _0;
  unsigned  _1;
  unsigned  _2;
  unsigned  _3;
  unsigned  _4;
  unsigned  _5;
  unsigned  _6;
  unsigned  _7;
  unsigned  _8;
  unsigned  maxMemoryAllocationCount;
  unsigned  _9;
  uint64_t  bufferImageGranularity;
  uint64_t  _10;
  unsigned  _11;
  unsigned  _12;
  unsigned  _13;
  unsigned  _14;
  unsigned  _15;
  unsigned  _16;
  unsigned  _17;
  unsigned  _18;
  unsigned  _19;
  unsigned  _20;
  unsigned  _21;
  unsigned  _22;
  unsigned  _23;
  unsigned  _24;
  unsigned  _25;
  unsigned  _26;
  unsigned  _27;
  unsigned  _28;
  unsigned  _29;
  unsigned  _30;
  unsigned  _31;
  unsigned  _32;
  unsigned  _33;
  unsigned  _34;
  unsigned  _35;
  unsigned  _36;
  unsigned  _37;
  unsigned  _38;
  unsigned  _39;
  unsigned  _40;
  unsigned  _41;
  unsigned  _42;
  unsigned  _43;
  unsigned  _44;
  unsigned  _45;
  unsigned  _46;
  unsigned  _47;
  unsigned  _48;
  unsigned  _49;
  unsigned  _50[3];
  unsigned  _51;
  unsigned  _52[3];
  unsigned  _53;
  unsigned  _54;
  unsigned  _55;
  unsigned  _56;
  unsigned  _57;
  float     _58;
  float     _59;
  unsigned  _60;
  unsigned  _61[2];
  float     _62[2];
  unsigned  _63;
  size_t    _64;
  uint64_t  _65;
  uint64_t  _66;
  uint64_t  _67;
  int       _68;
  unsigned  _69;
  int       _70;
  unsigned  _71;
  float     _72;
  float     _73;
  unsigned  _74;
  unsigned  _75;
  unsigned  _76;
  unsigned  _77;
  unsigned  _78;
  unsigned  _79;
  unsigned  _80;
  unsigned  _81;
  unsigned  _82;
  unsigned  _83;
  unsigned  _84;
  unsigned  _85;
  unsigned  _86;
  unsigned  _87;
  unsigned  _88;
  RedBool32 _89;
  float     _90;
  unsigned  _91;
  unsigned  _92;
  unsigned  _93;
  unsigned  _94;
  float     _95[2];
  float     _96[2];
  float     _97;
  float     _98;
  RedBool32 _99;
  RedBool32 _100;
  uint64_t  _101;
  uint64_t  _102;
  uint64_t  nonCoherentAtomSize;
} RmaPhysicalDeviceLimits;

typedef struct RmaPhysicalDeviceSparseProperties {
  RedBool32 _0;
  RedBool32 _1;
  RedBool32 _2;
  RedBool32 _3;
  RedBool32 _4;
} RmaPhysicalDeviceSparseProperties;

typedef struct RmaPhysicalDeviceProperties {
  unsigned                          _0;
  unsigned                          _1;
  unsigned                          _2;
  unsigned                          _3;
  RedGpuType                        deviceType;
  char                              _4[256];
  unsigned char                     _5[16];
  RmaPhysicalDeviceLimits           limits;
  RmaPhysicalDeviceSparseProperties _6;
} RmaPhysicalDeviceProperties;

REDGPU_DECLSPEC void REDGPU_API rmaVkGetPhysicalDeviceProperties(RedContext context, unsigned gpuIndex, RedHandleGpuDevice physicalDevice, void * pVkPhysicalDeviceProperties) {
  RmaPhysicalDeviceProperties properties = {};
  properties.deviceType                      = context->gpus[gpuIndex].gpuType;
  properties.limits.maxMemoryAllocationCount = context->gpus[gpuIndex].maxMemoryAllocateCount;
  properties.limits.bufferImageGranularity   = context->gpus[gpuIndex].minMemoryPageSeparationArrayImageBytesCount;
  properties.limits.nonCoherentAtomSize      = context->gpus[gpuIndex].minMemoryNonCoherentBlockBytesCount;
  RmaPhysicalDeviceProperties * out = (RmaPhysicalDeviceProperties *)pVkPhysicalDeviceProperties;
  out[0] = properties;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkGetPhysicalDeviceMemoryProperties(RedContext context, unsigned gpuIndex, RedHandleGpuDevice physicalDevice, void * pVkPhysicalDeviceMemoryProperties) {
  VkPhysicalDeviceMemoryProperties properties = {};
  properties.memoryTypeCount = context->gpus[gpuIndex].memoryTypesCount;
  properties.memoryHeapCount = context->gpus[gpuIndex].memoryHeapsCount;
  for (unsigned i = 0; i < context->gpus[gpuIndex].memoryTypesCount; i += 1) {
    RedMemoryType memoryType = context->gpus[gpuIndex].memoryTypes[i];
    properties.memoryTypes[i].heapIndex = memoryType.memoryHeapIndex;
    if (memoryType.isGpuVram == 1) {
      properties.memoryTypes[i].propertyFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    }
    if (memoryType.isCpuMappable == 1) {
      properties.memoryTypes[i].propertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
    }
    if (memoryType.isCpuCoherent == 1) {
      properties.memoryTypes[i].propertyFlags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    }
    if (memoryType.isCpuCached == 1) {
      properties.memoryTypes[i].propertyFlags |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
    }
  }
  for (unsigned i = 0; i < context->gpus[gpuIndex].memoryHeapsCount; i += 1) {
    RedMemoryHeap memoryHeap = context->gpus[gpuIndex].memoryHeaps[i];
    properties.memoryHeaps[i].size = memoryHeap.memoryBytesCount;
    if (memoryHeap.isGpuVram == 1) {
      properties.memoryHeaps[i].flags |= VK_MEMORY_HEAP_DEVICE_LOCAL_BIT;
    }
  }
  VkPhysicalDeviceMemoryProperties * out = (VkPhysicalDeviceMemoryProperties *)pVkPhysicalDeviceMemoryProperties;
  out[0] = properties;
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkAllocateMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkMemoryAllocateInfo, const void * pVkAllocationCallbacks, RedHandleMemory * pMemory) {
  const VkMemoryAllocateInfo * memoryAllocateInfo = (const VkMemoryAllocateInfo *)pVkMemoryAllocateInfo;
  RedStatuses statuses = {};
  if (context->gpus[gpuIndex].memoryTypes[memoryAllocateInfo->memoryTypeIndex].isCpuMappable == 1) {
    // NOTE(Constantine): Pass array from VMA to RMA in future.
    RedHandleArray array = 0;
    redMemoryAllocateMappable(context, device, "REDGPU Memory Allocator", 0, array, memoryAllocateInfo->allocationSize, memoryAllocateInfo->memoryTypeIndex, 0, pMemory, &statuses, 0, 0, 0);
  } else {
    redMemoryAllocate(context, device, "REDGPU Memory Allocator", memoryAllocateInfo->allocationSize, memoryAllocateInfo->memoryTypeIndex, 0, 0, 0, pMemory, &statuses, 0, 0, 0);
  }
  return statuses.statusError;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkFreeMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory, const void * pVkAllocationCallbacks) {
  redMemoryFree(context, device, memory, 0, 0, 0);
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkMapMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory, uint64_t offset, uint64_t size, unsigned vkMemoryMapFlags, void ** ppData) {
  RedStatuses statuses = {};
  redMemoryMap(context, device, memory, offset, size, ppData, &statuses, 0, 0, 0);
  return statuses.statusError;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkUnmapMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleMemory memory) {
  redMemoryUnmap(context, device, memory, 0, 0, 0);
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkFlushMappedMemoryRanges(RedContext context, unsigned gpuIndex, RedHandleGpu device, unsigned memoryRangeCount, const void * pVkMappedMemoryRange) {
  RedStatuses statuses = {};
  redMemoryNonCoherentFlush(context, device, memoryRangeCount, (const RedMappableMemoryRange *)pVkMappedMemoryRange, &statuses, 0, 0, 0);
  return statuses.statusError;
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkInvalidateMappedMemoryRanges(RedContext context, unsigned gpuIndex, RedHandleGpu device, unsigned memoryRangeCount, const void * pVkMappedMemoryRange) {
  RedStatuses statuses = {};
  redMemoryNonCoherentInvalidate(context, device, memoryRangeCount, (const RedMappableMemoryRange *)pVkMappedMemoryRange, &statuses, 0, 0, 0);
  return statuses.statusError;
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkBindBufferMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, RedHandleMemory memory, uint64_t memoryOffset) {
  RedStatuses statuses = {};
  RedMemoryArray memoryArray = {};
  memoryArray.setTo1000157000  = 1000157000;
  memoryArray.setTo0           = 0;
  memoryArray.array            = buffer;
  memoryArray.memory           = memory;
  memoryArray.memoryBytesFirst = memoryOffset;
  redMemorySet(context, device, 1, &memoryArray, 0, 0, &statuses, 0, 0, 0);
  return statuses.statusError;
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkBindImageMemory(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, RedHandleMemory memory, uint64_t memoryOffset) {
  RedStatuses statuses = {};
  RedMemoryImage memoryImage = {};
  memoryImage.setTo1000157001  = 1000157001;
  memoryImage.setTo0           = 0;
  memoryImage.image            = image;
  memoryImage.memory           = memory;
  memoryImage.memoryBytesFirst = memoryOffset;
  redMemorySet(context, device, 0, 0, 1, &memoryImage, &statuses, 0, 0, 0);
  return statuses.statusError;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkGetBufferMemoryRequirements(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, void * pVkMemoryRequirements) {
  RedArray arrayData = __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArrays[buffer];
  VkMemoryRequirements * out = (VkMemoryRequirements *)pVkMemoryRequirements;
  out->size           = arrayData.memoryBytesCount;
  out->alignment      = arrayData.memoryBytesAlignment;
  out->memoryTypeBits = arrayData.memoryTypesSupported;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkGetImageMemoryRequirements(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, void * pVkMemoryRequirements) {
  RedImage imageData = __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImages[image];
  VkMemoryRequirements * out = (VkMemoryRequirements *)pVkMemoryRequirements;
  out->size           = imageData.memoryBytesCount;
  out->alignment      = imageData.memoryBytesAlignment;
  out->memoryTypeBits = imageData.memoryTypesSupported;
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkCreateBuffer(RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkBufferCreateInfo, const void * pVkAllocationCallbacks, RedHandleArray * pBuffer) {
  const VkBufferCreateInfo * createInfo = (const VkBufferCreateInfo *)pVkBufferCreateInfo;
  RedStatuses statuses = {};
  RedArrayType arrayType = RED_ARRAY_TYPE_ARRAY_RW;
  if ((createInfo->usage & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) == VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) {
    arrayType = RED_ARRAY_TYPE_ARRAY_RO_CONSTANT;
  } else if ((createInfo->usage & VK_BUFFER_USAGE_INDEX_BUFFER_BIT) == VK_BUFFER_USAGE_INDEX_BUFFER_BIT) {
    arrayType = RED_ARRAY_TYPE_INDEX_RO;
  }
  // NOTE(Constantine): Pass structuredBufferElementBytesCount from VMA to RMA in future.
  uint64_t structuredBufferElementBytesCount = 0;
  // NOTE(Constantine): Pass initialAccess from VMA to RMA in future.
  RedAccessBitflags initialAccess = 0;
  // NOTE(Constantine): Pass initialQueueFamilyIndex from VMA to RMA in future.
  unsigned initialQueueFamilyIndex = 0;
  RedArray array = {};
  redCreateArray(context, device, "REDGPU Memory Allocator", arrayType, createInfo->size, structuredBufferElementBytesCount, initialAccess, createInfo->sharingMode == VK_SHARING_MODE_CONCURRENT ? -1 : initialQueueFamilyIndex, 0, &array, &statuses, 0, 0, 0);
  pBuffer[0] = array.handle;
  {
    std::lock_guard<std::mutex> __mapArraysMutexScope(__REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArraysMutex);
    __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArrays[array.handle] = array;
  }
  return statuses.statusError;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkDestroyBuffer(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleArray buffer, const void * pVkAllocationCallbacks) {
  redDestroyArray(context, device, buffer, 0, 0, 0);
  {
    std::lock_guard<std::mutex> __mapArraysMutexScope(__REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArraysMutex);
    __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapArrays.erase(buffer);
  }
}

REDGPU_DECLSPEC RedStatus REDGPU_API rmaVkCreateImage(RedContext context, unsigned gpuIndex, RedHandleGpu device, const void * pVkImageCreateInfo, const void * pVkAllocationCallbacks, RedHandleImage * pImage) {
  const VkImageCreateInfo * createInfo = (const VkImageCreateInfo *)pVkImageCreateInfo;
  RedStatuses statuses = {};
  RedImageDimensions imageDimensions = RED_IMAGE_DIMENSIONS_2D;
  if (createInfo->imageType == VK_IMAGE_TYPE_1D) {
    imageDimensions = RED_IMAGE_DIMENSIONS_1D;
  } else if (createInfo->imageType == VK_IMAGE_TYPE_2D && ((createInfo->flags & VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT) == VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)) {
    imageDimensions = RED_IMAGE_DIMENSIONS_2D_WITH_TEXTURE_DIMENSIONS_CUBE_AND_CUBE_LAYERED;
  } else if (createInfo->imageType == VK_IMAGE_TYPE_2D) {
    imageDimensions = RED_IMAGE_DIMENSIONS_2D;
  } else if (createInfo->imageType == VK_IMAGE_TYPE_3D && ((createInfo->flags & VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT) == VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT)) {
    imageDimensions = RED_IMAGE_DIMENSIONS_3D_WITH_TEXTURE_DIMENSIONS_2D_AND_2D_LAYERED;
  } else if (createInfo->imageType == VK_IMAGE_TYPE_3D) {
    imageDimensions = RED_IMAGE_DIMENSIONS_3D;
  }
  RedAccessBitflags restrictToAccess = 0;
  if ((createInfo->usage & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) == VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_COPY_R;
  }
  if ((createInfo->usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT) == VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_COPY_W;
  }
  if ((createInfo->usage & VK_IMAGE_USAGE_SAMPLED_BIT) == VK_IMAGE_USAGE_SAMPLED_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_STRUCT_RESOURCE_NON_FRAGMENT_STAGE_R | RED_ACCESS_BITFLAG_STRUCT_RESOURCE_FRAGMENT_STAGE_R;
  }
  if ((createInfo->usage & VK_IMAGE_USAGE_STORAGE_BIT) == VK_IMAGE_USAGE_STORAGE_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_STRUCT_RESOURCE_W;
  }
  if ((createInfo->usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) == VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_OUTPUT_COLOR_W;
  }
  if ((createInfo->usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    restrictToAccess |= RED_ACCESS_BITFLAG_OUTPUT_DEPTH_RW;
    if ((RedFormat)createInfo->format == RED_FORMAT_DEPTH_24_UINT_TO_FLOAT_0_1_STENCIL_8_UINT ||
        (RedFormat)createInfo->format == RED_FORMAT_DEPTH_32_FLOAT_STENCIL_8_UINT)
    {
      restrictToAccess |= RED_ACCESS_BITFLAG_OUTPUT_STENCIL_RW;
    }
  }
  // NOTE(Constantine): Pass initialAccess from VMA to RMA in future.
  RedAccessBitflags initialAccess = 0;
  // NOTE(Constantine): Pass initialQueueFamilyIndex from VMA to RMA in future.
  unsigned initialQueueFamilyIndex = 0;
  RedImage image = {};
  redCreateImage(context, device, "REDGPU Memory Allocator", imageDimensions, (RedFormat)createInfo->format, createInfo->extent.width, createInfo->extent.height, createInfo->extent.depth, createInfo->mipLevels, createInfo->arrayLayers, (RedMultisampleCountBitflag)createInfo->samples, restrictToAccess, initialAccess, createInfo->sharingMode == VK_SHARING_MODE_CONCURRENT ? -1 : initialQueueFamilyIndex, 0, &image, &statuses, 0, 0, 0);
  pImage[0] = image.handle;
  {
    std::lock_guard<std::mutex> __mapImagesMutexScope(__REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImagesMutex);
    __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImages[image.handle] = image;
  }
  return statuses.statusError;
}

REDGPU_DECLSPEC void REDGPU_API rmaVkDestroyImage(RedContext context, unsigned gpuIndex, RedHandleGpu device, RedHandleImage image, const void * pVkAllocationCallbacks) {
  redDestroyImage(context, device, image, 0, 0, 0);
  {
    std::lock_guard<std::mutex> __mapImagesMutexScope(__REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImagesMutex);
    __REDGPU_MEMORY_ALLOCATOR_FUNCTIONS_GLOBAL_ec8b2cdda35a8068bba6ef47ad511ac00d5c39d6_mapImages.erase(image);
  }
}

REDGPU_DECLSPEC void REDGPU_API rmaVkCmdCopyBuffer(RedContext context, unsigned gpuIndex, RedHandleCalls commandBuffer, RedHandleArray srcBuffer, RedHandleArray dstBuffer, unsigned regionCount, const void * pVkBufferCopy) {
  RedCallProceduresAndAddresses callPAs = {};
  redGetCallProceduresAndAddresses(context, context->gpus[gpuIndex].gpu, &callPAs, 0, 0, 0, 0);
  callPAs.redCallCopyArrayToArray(commandBuffer, srcBuffer, dstBuffer, regionCount, (const RedCopyArrayRange *)pVkBufferCopy);
}