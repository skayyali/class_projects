package heap;

import global.GlobalConst;

public class Tuple implements GlobalConst {
	public static final int max_size = PAGE_SIZE;
	public byte[] data;
	private int tuple_offset;
	private int tuple_length;

	public Tuple() {
		data = new byte[max_size];
		tuple_offset = 0;
		tuple_length = max_size;
	}

	public Tuple(byte[] atupl) {
		data = atupl;
		tuple_offset = 0;
		tuple_length = atupl.length;
	}

	public Tuple(byte[] atuple, int offset, int length) {
		data = atuple;
		tuple_offset = offset;
		tuple_length = length;
	}

	public Tuple(int size) {
		data = new byte[size];
		tuple_offset = 0;
		this.tuple_length = size;
	}

	public byte[] getTupleByteArray() {
		return data;
	}

	public int getLength() {
		return tuple_length;
	}

	public void setData(byte[] data) {
		this.data = data;
	}

	public void setlength(int tuple_length) {
		this.tuple_length = tuple_length;
	}

	public int getTuple_offset() {
		return tuple_offset;
	}

	public void setTuple_offset(int tuple_offset) {
		this.tuple_offset = tuple_offset;
	}

}