package com.bakk.scripts;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class Convertor {

	public static void main(String[] args) {
		String usage = "Usage: java -jar convertor.jar <path to txt> <target path>";
		if (args.length != 2) {
			System.out.println(usage);
		}
		if(!(new File(args[0]).canRead())){
			System.out.println("Input file does not exist!\n" + usage);
		}
		List<OBDCommand> input  = new ArrayList<OBDCommand>();
		try {
			BufferedReader txtInput = new BufferedReader(new FileReader(args[0]));
			for(String line; (line = txtInput.readLine()) != null; ) {
		        OBDCommand parsedCommand = new OBDCommand();
				String[] splitted = line.split(";");
		        if(splitted.length == 2){
		        	initTableAndIds(parsedCommand, splitted[0]);
		        	parsedCommand.description = splitted[1];
		        }
		        input.add(parsedCommand);
		    }
			
			BufferedWriter sqlOutput = new BufferedWriter(new FileWriter(args[1]));
			for(OBDCommand command : input){
				sqlOutput.append(command.toString());
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println(usage);
		}

	}

	private static void initTableAndIds(OBDCommand parsedCommand, String code) {
		parsedCommand.table = OBDCommand.tablemapping.get(code.substring(0, 1));
		try{
			parsedCommand.completeId = Integer.parseInt(code.substring(1,code.length()), 16);
			parsedCommand.codeClassId = Integer.parseInt(code.substring(1,2), 16);
			parsedCommand.sourceClassId = Integer.parseInt(code.substring(2,3), 16);
			parsedCommand.faultId = Integer.parseInt(code.substring(3,5), 16);
		}catch (Exception e ){
			e.printStackTrace();
			System.exit(1);
		}
	}

}
