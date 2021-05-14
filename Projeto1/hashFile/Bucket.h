
struct OverflowBucket {
    int first_block_addr;
    int first_block_offset;
	int last_block_addr;
    int last_block_offset;
};

class Bucket {
	public:
		int block_addr;
		OverflowBucket overflow;
		int numberOfRecords;
		Bucket();
		void setBlockAddr(int block_addr);
		void setNumberOfRecords(int numberOfRecords);
		void incrementNumberOfRecords();
		void decrementNumberOfRecords();
};