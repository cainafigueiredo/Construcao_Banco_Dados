
struct OverflowBucket {
    int block_addr;
    int block_offset;
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