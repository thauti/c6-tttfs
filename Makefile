all: 
	make -C libll/
	make -C tfs_utils/analyze/
	make -C tfs_utils/create/
	make -C tfs_utils/format/
	make -C tfs_utils/partition/
	make -C libtfs/

clean:
	rm libll/*.o
	rm tfs_utils/analyze/*.o
	rm tfs_utils/create/*.o
	rm tfs_utils/format/*.o
	rm tfs_utils/partition/*.o
	rm libtfs/*.o