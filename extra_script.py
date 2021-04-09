Import("env")

#
# Dump build environment (for debug)
# print(env.Dump())
#

env.Append(
  LINKFLAGS=[
      "-mthumb",
       "-mcpu=cortex-m4",
      "-mfloat-abi=hard",
       "-mfpu=fpv4-sp-d16"
  ]
)