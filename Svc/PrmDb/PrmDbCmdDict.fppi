@ Command to save parameter image to file. Uses file name passed to constructor
async command PRM_SAVE_FILE \
  opcode 0x00


@ Loads a file from storage and updates the volatile values for the parameters defined in the file. The file could have selective IDs and not the whole set.
async command PRM_SET_FILE(
  fileName: string size 100 @< The name of the on-board file to set parameters format
  ) \
  opcode 0x01
