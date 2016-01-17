package com.bakk.scripts;

import java.util.HashMap;
import java.util.Map;

public class OBDCommand {
	public String table;
	public int completeId;
	public int codeClassId;
	public int sourceClassId;
	public int faultId;
	public String description;
	public String diagnosis;

	public static Map<String, String> tablemapping = new HashMap<String, String>() {
		{
			put("P", "Powertrain");
		}
		{
			put("C", "Chassis");
		}
		{
			put("U", "Network");
		}
		{
			put("B", "Body");
		}
	};

	@Override
	public String toString() {
		return "INSERT INTO `" + table + "` (`ID`, `ID_CodeClass`, `ID_Source`, `ID_Fault`, `ShortDescription`, `Diagnosis`) " +
				"VALUES (" +
				completeId + "," + codeClassId + "," + sourceClassId + "," + faultId + "," + "'" + description + "'" +  "," + "'" + diagnosis + "'" +
				");\n";
	}
}
