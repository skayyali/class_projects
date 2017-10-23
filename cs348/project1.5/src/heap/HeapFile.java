package heap;
import global.*;

import java.lang.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class HeapFile {
		private String name;
		private PageId firstPage;
		private HFPage firstHFPage;
		private PageId lastPage;
		private int recCnt;
		
		//private ArrayList<PageId> pageList;
		private TreeMap<Integer, PageId> pageList;
		private TreeMap<Integer, PageId> pageFullList;
		
	public HeapFile(String name) {
		this.name = name;
		
		
		pageList = new TreeMap<Integer, PageId>();
		pageFullList = new TreeMap<Integer, PageId>();
		
		
		
		//CHECK if file exists:
		HFPage currentHFPage = new HFPage();;
		firstHFPage = new HFPage();
		PageId firstPageId = global.Minibase.DiskManager.get_file_entry(name);
		//if file does not exist, make new file
		if (firstPageId == null) {
			firstPageId = global.Minibase.BufferManager.newPage(currentHFPage, 1);
			currentHFPage.setCurPage(firstPageId);
			//System.out.println("###TEST888:   "+  "PAGE ID:" +currentHFPage.getCurPage().pid+" #########");
			global.Minibase.DiskManager.add_file_entry(name, firstPageId);
			
			pageList.put(firstPageId.pid, firstPageId);
			
			recCnt = 0;
			//System.out.println("###FREE SPACE in:"+  "PAGE ID:" + firstPageId.pid + "    "+ currentHFPage.getFreeSpace()+" #########");
			firstPage = firstPageId;
			firstHFPage.copyPage(currentHFPage);
			lastPage = firstPageId;
			global.Minibase.BufferManager.unpinPage(firstPageId, true);
			//System.out.println("###TEST:   "+  "CREATED FIRST PAGE!" + "#########");
			
			return;			
		}
		
		global.Minibase.BufferManager.pinPage(firstPageId, currentHFPage, false);
		currentHFPage.setCurPage(firstPageId);
		recCnt = 0;

		
		firstPage = firstPageId;
		lastPage = firstPageId;
		global.Minibase.BufferManager.unpinPage(firstPageId, false);
		
		
		PageId currentPage = firstPageId;
		while (currentPage.pid > 0) {
			HFPage temp = new HFPage();
			global.Minibase.BufferManager.pinPage(currentPage, temp, false);
			
			
			if(temp.getFreeSpace() < 5) {				//page is full, add to full list
				pageFullList.put(currentPage.pid, firstPageId);
				
				//System.out.println("ADDING " + firstPageId.pid + "  to page full list");
				//System.out.println("NEXT PAGE: " + temp.getNextPage().pid);
				recCnt = recCnt + recordCount(temp);
				global.Minibase.BufferManager.unpinPage(currentPage, false);
				lastPage = currentPage;
				currentPage = temp.getNextPage();
				
			} else {									//page is not full, add to page list
				pageList.put(currentPage.pid, firstPageId);
				recCnt = recCnt + recordCount(temp);
				//System.out.println("ADDING " + firstPageId.pid + "  to page list");
				//System.out.println("NEXT PAGE: " + temp.getNextPage().pid);
				global.Minibase.BufferManager.unpinPage(currentPage, false);
				lastPage = currentPage;
				currentPage = temp.getNextPage();
				
			}
			
		}
		
	}
	
	private int recordCount(HFPage page) {
		RID rid = page.firstRecord();
		int count = 0;
		while (rid != null) {
			rid = page.nextRecord(rid);
			count++;
		}
		return count;
	}

	public RID insertRecord(byte[] record) {
		//loop only through 'not full' list
		//System.out.println("INSERT RECORD");
		for(Map.Entry<Integer, PageId> entry : pageList.entrySet()) {
			PageId pid = entry.getValue();
			HFPage hfpage = new HFPage();
			global.Minibase.BufferManager.pinPage(pid, hfpage, false);
			hfpage.setCurPage(pid);
			//System.out.println("###INITIAL FREE SPACE IN PAGE ID:"  + pid.pid + "----"+ hfpage.getFreeSpace()+"BYTES   #########");
			//System.out.println("###TEST420:   "+  "PAGE ID:" +hfpage.getCurPage().pid+" #########");

			
			
			//System.out.println("###TEST:   "+  "TRYING TO ADD RECORD TO PAGE: " + pid.pid + "#########");
			if (hfpage.getFreeSpace() >= record.length + 4) {
				RID rid = hfpage.insertRecord(record);
				recCnt++;
				//System.out.println("ADDING  " + record.length + " bytes");
				if (hfpage.getFreeSpace() < 5) { //if page now full, move from free list to full list
					pageList.remove(pid.pid);
					pageFullList.put(pid.pid, pid);
					//System.out.println("HERE WE ARE ADDED TO pageFullList : " + pid.pid );
				}
				global.Minibase.BufferManager.unpinPage(pid, true);
				//System.out.println("###TEST:   "+  "ADDED RECORD: " + Convert.getIntValue (0, record) +"    "+ Convert.getFloatValue (4, record)  +" TO PAGE :" +pid.pid+ "!   #########");
				//System.out.println("###FREE SPACE in:"+  "PAGE ID:" + pid.pid + "    "+  hfpage.getFreeSpace()+" #########\n");
				//System.out.println("LASTPAGE NOW:  " +lastPage.pid+"   FIRSTPAGE STILL:   "+firstPage.pid);
				
				return rid;
			}
			global.Minibase.BufferManager.unpinPage(pid, false);
		}
		
		//System.out.println("########################################");
		//System.out.println("########################################");
		//System.out.println("########################################");
		//System.out.println("NOT ENOUGH SPACE ON PAGES, CREATING NEW PAGE");
		//not enough space in pages; create new page
		HFPage hfpage = new HFPage();
		PageId pid = global.Minibase.BufferManager.newPage(hfpage, 1);
		hfpage.setCurPage(pid);
		

		
		hfpage.setPrevPage(lastPage);
		hfpage.setNextPage(new PageId(-1));
		
		HFPage temp = new HFPage();
		global.Minibase.BufferManager.pinPage(lastPage, temp, false);
		
		temp.setNextPage(pid);
		
		RID rid = hfpage.insertRecord(record);
		recCnt++;
		pageList.put(pid.pid, pid);
		//System.out.println("ADDED TO pageList : " + pid.pid);
		
		//System.out.println("***** "+  "ADDED RECORD: " + Convert.getIntValue (0, record) +"    "+ Convert.getFloatValue (4, record)  +" TO PAGE :" +pid.pid+ "!   #########");
		//System.out.println("###FREE SPACE in:"+  "PAGE ID:" + pid.pid + "    "+  hfpage.getFreeSpace()+" #########\n");
		
		global.Minibase.BufferManager.unpinPage(pid, true);
		global.Minibase.BufferManager.unpinPage(lastPage, true);
		
		lastPage = pid;
		//System.out.println("LASTPAGE NOW:  " +lastPage.pid+"   FIRSTPAGE STILL:   "+firstPage.pid);
		//System.out.println("########################################");
		//System.out.println("########################################");
		//System.out.println("########################################");
		//System.out.println("RETURNING RID:  " + rid.pageno.pid + "   -   " + rid.slotno);
		
		return rid;
		
	}
	
	public Tuple getRecord(RID rid) {
		if(!pageList.containsKey(rid.pageno.pid) && !pageFullList.containsKey(rid.pageno.pid))
			throw new IllegalArgumentException("Invalid RID");
		PageId pid = new PageId(rid.pageno.pid);
		HFPage page = new HFPage();
		global.Minibase.BufferManager.pinPage(pid, page, false);
		try {
			byte[] recArray = page.selectRecord(rid);
			global.Minibase.BufferManager.unpinPage(pid, false);
			return new Tuple(recArray, 0, recArray.length);
			
		} catch (Exception e) {
			global.Minibase.BufferManager.unpinPage(pid, false);
			return null;
			
		}
		
	}
	
	public boolean updateRecord(RID rid, Tuple newRecord) {
		//System.out.println("UPDATING: " + rid.pageno + " -- " + rid.slotno);
		if(!pageList.containsKey(rid.pageno.pid) && !pageFullList.containsKey(rid.pageno.pid))
			throw new IllegalArgumentException("Invalid RID");
		PageId pid = new PageId(rid.pageno.pid);
		//System.out.println("PID:" + pid.pid);
		Page temp = new Page();
		HFPage page = new HFPage();
		global.Minibase.BufferManager.pinPage(pid, page, false);
		page.setCurPage(pid);
		try {
			Tuple t = getRecord(rid);
			if(newRecord.getLength() != t.getLength()) {
				global.Minibase.BufferManager.unpinPage(pid, false);
				throw new IllegalArgumentException("Invalid size");

			} else {
				//byte[] updatedArray = newRecord.getTupleByteArray();
				page.updateRecord(rid, newRecord);
				global.Minibase.BufferManager.unpinPage(pid, true);
				return true;
			}
			
		} catch (Exception e) {
			global.Minibase.BufferManager.unpinPage(pid, false);
		}
		
		
		
		return false;
		
	}
	
	public boolean deleteRecord(RID rid) {
		//System.out.println("DELETING RID:  " + rid.pageno.pid + "   -   " + rid.slotno);
		
		
		//Tuple t1 = getRecord(rid);
		//byte[] array = t1.getTupleByteArray();
		//System.out.println("GOT TUPLE:   " + Convert.getIntValue (0, array));

		if(pageList.containsKey(rid.pageno.pid)) {
			PageId pid = new PageId(rid.pageno.pid);
			HFPage page = new HFPage();
			global.Minibase.BufferManager.pinPage(pid, page, false);
			try {
				Tuple t = getRecord(rid);
				int size = t.getLength();
				page.deleteRecord(rid);
				recCnt--;
				
				global.Minibase.BufferManager.unpinPage(pid, false);
				return true;
				
			} catch (Exception e) {
				global.Minibase.BufferManager.unpinPage(pid, false);
			}
		} else if (pageFullList.containsKey(rid.pageno.pid)) {
			PageId pid = new PageId(rid.pageno.pid);
			HFPage page = new HFPage();
			global.Minibase.BufferManager.pinPage(pid, page, false);
			try {
				Tuple t = getRecord(rid);
				page.deleteRecord(rid);
				recCnt--;
				
				pageFullList.remove(pid.pid);
				pageList.put(pid.pid, pid);
				
				global.Minibase.BufferManager.unpinPage(pid, false);
				return true;
				
			} catch (Exception e) {
				global.Minibase.BufferManager.unpinPage(pid, false);
			}
		} else {
			throw new IllegalArgumentException("Invalid RID");
		}
		
		
		return false;
		
	}
	
	public int getRecCnt() {
		return recCnt;
		
	}
	
	public HeapScan openScan() {
		return new HeapScan(this);
	}

	public PageId getFirstPageID() {
		return firstPage;
	}
	
	public HFPage getFirstHFPage() {
		return firstHFPage;
	}

}
