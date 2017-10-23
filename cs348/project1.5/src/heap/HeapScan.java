package heap;
import global.*;

import java.lang.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

import chainexception.ChainException;


public class HeapScan {
	private HeapFile file;
	private HFPage currentHFPage;
	private RID currentRID;
	
	private PageId firstPage;
	
	
	protected HeapScan(HeapFile file) {
		this.file = file;
		firstPage = file.getFirstPageID();
		//System.out.println("\n-------------------------------");
		//System.out.println("HEAPSCAN INITIALIZATION");
		//System.out.println("-------------------------------\n");
		currentHFPage = new HFPage();
		currentHFPage.setCurPage(firstPage);
		//System.out.println("RECIEVED FIRSTPAGE: " + firstPage.pid);
		global.Minibase.BufferManager.pinPage(firstPage, currentHFPage, false);
		//currentHFPage = new HFPage(page);
		currentRID = currentHFPage.firstRecord();
		//System.out.println("Current RID = !: " + currentRID.pageno.pid + " : " + currentRID.slotno);
		//currentHFPage.setCurPage(firstPage);
		if(currentRID == null)
			System.out.println("NULL RID ERROR");
		//System.out.println("HI!: " + currentRID.pageno.pid + "  +  " + currentRID.slotno);
	}
	
	
	public Tuple getNext(RID rid) {
		Tuple tuple = null;
		
		if(rid == null)
			rid = new RID();
		if (currentRID != null) {
			rid.copyRID(currentRID);
			tuple = new Tuple(currentHFPage.selectRecord(currentRID), 0, currentHFPage.selectRecord(currentRID).length);
			
			
			currentRID = currentHFPage.nextRecord(currentRID);
			byte[] array1 = tuple.getTupleByteArray();
			//System.out.println("//testttt/////"+currentHFPage.getCurPage().pid);
			//System.out.println("//testttt/////"+Convert.getIntValue (0, array1));
		}
		//System.out.println("HIIIII: " + rid.slotno);
		if (currentRID == null) {
			global.Minibase.BufferManager.unpinPage(currentHFPage.getCurPage(), false);
			if(currentHFPage.getNextPage().pid > 0)
			{
				PageId nextPage = currentHFPage.getNextPage();
				currentHFPage = new HFPage();
				global.Minibase.BufferManager.pinPage(nextPage, currentHFPage, false);
				currentRID = currentHFPage.firstRecord();
				
			}
			else 
			{
				global.Minibase.BufferManager.pinPage(currentHFPage.getCurPage(), currentHFPage, false);
				//System.out.println("I am here: trying to unpin pid:" + currentHFPage.getCurPage().pid);
				//global.Minibase.BufferManager.unpinPage(currentHFPage.getCurPage(), false);				
			}
		}
		if(tuple == null) {
			//System.out.println("I am here 2: trying to unpin pid:" + currentHFPage.getCurPage().pid);
			global.Minibase.BufferManager.unpinPage(currentHFPage.getCurPage(), false);
			return null;
		}
		
		byte[] array = tuple.getTupleByteArray();
		//System.out.println("###returning:   "+ Convert.getIntValue (0, array)+ "from pid: " + currentHFPage.getCurPage().pid+" #########");
		return tuple;
	}
	
	public boolean hasNext() {
		//FIX THIS
		return true;
	}
	
	public void close() throws ChainException {
		//global.Minibase.BufferManager.unpinPage(currentHFPage.getCurPage(), false);
		
		try {
			finalize();
		} catch (Throwable e) {
			e.printStackTrace();
		}
		//System.out.println("\n-------------------------------");
		//System.out.println("HEAPSCAN CLOSE");
		//System.out.println("-------------------------------\n");
	}
	
	protected void finalize() throws Throwable {
		file = null;
		currentHFPage = null;
		currentRID = null;
		firstPage = null;
	}
}
