all: 
	make -C libll/
	make -C tfs_utils/analyze
	make -C tfs_utils/create
	make -C tfs_utils/format
	make -C tfs_utils/partition
	make -C libtfs/
