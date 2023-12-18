import com.mongodb.MongoClient;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;
import org.bson.Document;

import java.util.ArrayList;
import java.util.Scanner;

public class MongoConnect {
    static MongoCollection<Document> collection;
    static Scanner sc = new Scanner(System.in);
    static MongoClient mongo;

    public static void init() throws Exception {
        mongo = new MongoClient("localhost", 27017);

        // Prompt the user for the database and collection names
        System.out.print("Enter the database name: ");
        String dbName = sc.next();
        System.out.print("Enter the collection name: ");
        String collectionName = sc.next();

        MongoDatabase db = mongo.getDatabase(dbName);
        // Create the collection if it doesn't exist
        if (!db.listCollectionNames().into(new ArrayList<>()).contains(collectionName)) {
            db.createCollection(collectionName);
        }
        collection = db.getCollection(collectionName);
        System.out.println("Connection Established...");
    }

    public static void insertRecords() {
        System.out.println("Enter the data for the new record:");
        Document doc = new Document();

        System.out.print("Enter the unique field name (e.g., roll, id): ");
        String uniqueFieldName = sc.next();
        System.out.print("Enter the value for the unique field: ");
        String uniqueFieldValue = sc.next();

        doc.append(uniqueFieldName, uniqueFieldValue);

        // Prompt the user for field names and values
        System.out.print("Enter the number of fields to add: ");
        int numFields = sc.nextInt();

        for (int i = 0; i < numFields; i++) {
            System.out.print("Enter the field name: ");
            String fieldName = sc.next();
            System.out.print("Enter the field value: ");
            String fieldValue = sc.next();
            doc.append(fieldName, fieldValue);
        }

        collection.insertOne(doc);
        System.out.println("Record Inserted!");
    }

    public static void readRecords() {
        FindIterable<Document> itr = collection.find();
        for (Document document : itr) {
            System.out.println(document);
        }
    }

    public static void updateRecords() {
        System.out.println("Enter the unique field name of the record to update: ");
        String uniqueFieldName = sc.next();
        System.out.println("Enter the value of the unique field: ");
        String uniqueFieldValue = sc.next();

        System.out.println("Enter the field name to update: ");
        String fieldName = sc.next();
        System.out.println("Enter the new value for the field: ");
        String updateValue = sc.next();

        collection.updateOne(
                Filters.eq(uniqueFieldName, uniqueFieldValue),
                Updates.set(fieldName, updateValue)
        );

        System.out.println("Record Updated!");
    }

    public static void deleteRecords() {
        System.out.println("Enter the unique field name of the record to delete: ");
        String uniqueFieldName = sc.next();
        System.out.println("Enter the value of the unique field: ");
        String uniqueFieldValue = sc.next();

        collection.deleteOne(Filters.eq(uniqueFieldName, uniqueFieldValue));
        System.out.println("Record Deleted!");
    }

    public static void main(String[] args) throws Exception {
        init();
        while (true) {
            System.out.println("---------Menu-------");
            System.out.println("1. Insert Records");
            System.out.println("2. Find Records");
            System.out.println("3. Update Records");
            System.out.println("4. Delete Records");
            System.out.println("5. Exit");
            System.out.print("Enter Your Choice: ");
            int choice = sc.nextInt();
            switch (choice) {
                case 1:
                    insertRecords();
                    break;
                case 2:
                    readRecords();
                    break;
                case 3:
                    updateRecords();
                    break;
                case 4:
                    deleteRecords();
                    break;
                case 5:
                    System.out.println("Thank You!");
                    mongo.close();
                    System.exit(0);
                default:
                    System.out.println("Please select an option from the above menu....!");
                    break;
            }
        }
    }
}

