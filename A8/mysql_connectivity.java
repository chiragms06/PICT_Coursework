package mypackage;

import java.util.*;
import java.sql.*;

public class MySQLConnectivity {

	public static void main(String[] args) throws Exception{
		System.out.println("Checking connection . . . .");
		
		try {
		Class.forName("com.mysql.cj.jdbc.Driver");
		String path = "jdbc:mysql://localhost:3306/connectivity";
		String username = "root";
		String password = "Chirag@11";
		
		Connection con = DriverManager.getConnection(path, username, password);
		Statement st = con.createStatement();
		ResultSet rs;
		
		if(con != null && !con.isClosed())
		{
			System.out.println("Database connected !\n");
		}
		else
		{
			System.out.println("Database not connected !\n");
		}
		
		String query, att, val, col, colval, ans, conval;
		boolean flag = true;
		String tablename;
		
		Scanner sc = new Scanner(System.in);
		
		while(flag)
		{
			System.out.println("\n=====MENU=====");
			System.out.println("1.CREATE TABLE");
			System.out.println("2.INSERT");
			System.out.println("3.SELECT");
			System.out.println("4.UPDATE");
			System.out.println("5.DELETE");
			System.out.println("6.EXIT");
			System.out.println("==============\n");
			
			System.out.println("Enter choice : ");
			int choice = sc.nextInt();
			
			switch(choice)
			{
			case 1: //create table
				query = "create table ";
				sc.nextLine();
				System.out.println("Enter table name : ");
				tablename = sc.nextLine();
				query += tablename + " ( ";
				
				
				System.out.println("Enter the column names with datatypes and constraints : ");
				att = sc.nextLine();
				
				query += att + " );";
				
				st.execute(query);
				System.out.println("Query > " + query);
				System.out.println("Table created successfully !!");
				break;
				
			case 2: //insert
				query = "insert into ";
				sc.nextLine();
				System.out.println("Enter table name : ");
				tablename = sc.nextLine();
				
				query += tablename + " values ( ";
				
				System.out.println("Enter values : ");
				val = sc.nextLine();
				
				query += val + " );";
				
				st.executeUpdate(query);
				System.out.println("Query > " + query);
				System.out.println("Data inserted successfully !!");
				break;
				
			case 3: //select
				sc.nextLine();
				System.out.println("Enter table name : ");
				tablename = sc.nextLine();
				
			    System.out.println("Do you want to display all columns (y/n) : ");
			    ans = sc.nextLine();

			    if ("y".equals(ans)) 
			    {
			        rs = st.executeQuery("SELECT * FROM " + tablename + ";");
			    } 
			    else 
			    {
			        System.out.println("Enter the column names you want to display (comma-separated) : ");
			        String selectedColumns = sc.nextLine();

			        query = "SELECT " + selectedColumns + " FROM " + tablename;
			        rs = st.executeQuery(query);
			    }

			    ResultSetMetaData rsmd = rs.getMetaData();
			    int columnCount = rsmd.getColumnCount();

			    for (int i = 1; i <= columnCount; i++)
			    {
			        System.out.print(rsmd.getColumnName(i) + "\t");
			    }
			    System.out.println();

			    while (rs.next())
			    {
			        for (int i = 1; i <= columnCount; i++)
			        {
			            System.out.print(rs.getString(i) + "\t");
			        }
			        System.out.println();
			    }

			    break;
			    
			case 4: //update
				sc.nextLine();
				System.out.println("Enter table name : ");
				tablename = sc.nextLine();
				
				query = "update " + tablename + " set ";
				
				System.out.println("Enter the column to be updated : ");
				col = sc.nextLine();
				
				query += col + " = ";
				
				System.out.println("Enter the updated value : ");
				colval = sc.nextLine();
				
				query += colval;
				
				System.out.println("Do you want to add any condition(y/n) : ");
				ans = sc.nextLine();
				if(ans.equals("y"))
				{
					System.out.println("Enter the condition : ");
					conval = sc.nextLine();
					query += " where " + conval;
				}
				
				st.executeUpdate(query);
				System.out.println("Query > " + query);
				System.out.println("Data updated successfully !!");
				break;
				
			case 5: //delete
				sc.nextLine();
				System.out.println("Enter table name : ");
				tablename = sc.nextLine();
				
				query = "delete from " + tablename;
				
				sc.nextLine();
				System.out.println("Do you want to add any condition(y/n) : ");
				ans = sc.nextLine();
				if(ans.equals("y"))
				{
					System.out.println("Enter the condition : ");
					conval = sc.nextLine();
					query += " where " + conval;
				}
				
				st.executeUpdate(query);
				System.out.println("Query > " + query);
				System.out.println("Data deleted successfully !!");
				break;
				
			case 6: //exit
				System.out.println("bye");
				flag = false;
				break;
				
			default:
				System.out.println("Invalid choice !");
				break;
					
			}
		}
		sc.close();
		st.close();
		con.close();
		
	}
		catch(Exception e)
		{
			System.out.println("\nError occurred !!\n");
			System.out.println(e);
		}

}
}

