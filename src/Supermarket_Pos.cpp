#include <bits/stdc++.h>
#include <iostream> 
using namespace std; 
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>


enum Payment_Type{
      Cash,
      Card,
      MB_WAY,
      Invalid_Payment_Option
    };

struct product_data{
    string description;
    double unitary_price;
    double iva;
    long long EAN13_code;

};

struct operation_data{
    //string state;
    vector<product_data> products;
    int total_price;
};

struct operation_receipt{
    string store_id;
    vector<product_data> products_bought;
    vector<double> received_payments;
    int bill_id;
    Payment_Type pt;
};

 Payment_Type resolvePaymentType(std::string input) {
    if( input == "-cash" ) return Cash;
    if( input == "-card" ) return Card;
    if( input == "-mbway" ) return MB_WAY;
    //Sort_nucleotide_AT_percentage
    return Invalid_Payment_Option;
}

/*std::ostream& operator<<(std::ostream& os, const Payment_Type PT)
{
  if(PT==Cash){
  os << "Cash";
  }
  if(PT==Card){
    os << "Card";
  }
  if(PT==MB_WAY){
    os << "MBWay";
  }
 return os;
}*/

 void menu(){
   cout << "Supermarket Point of Sale" << endl;
   cout << " 1: Identify Operator" << endl;
   cout << " 2: Close Operator" << endl;
 }

 /*Options resolveOption(std::string input) {
    if( input == "-h" ) return Help;
    if( input == "-V" ) return Version;
    if( input == "-v" ) return Verbose;
    if( input == "-sort=S" ) return Sort_size;
    if( input == "-sort=AT") return Sort_nucleotide_AT;
    if( input == "-sort=CG") return Sort_nucleotide_CG;
    if( input == "-sort=ATP") return Sort_nucleotide_AT_percentage;
    if( input == "-sort=CGP") return Sort_nucleotide_CG_percentage;
    if( input == "-sort=A" ) return Sort_alphabetically;
    if( input == "-s" ) return Shuffle;
    //Sort_nucleotide_AT_percentage
    return Option_Invalid;
}*/

long long generateEAN13code(){
    std::stringstream ss;
    const int size = 13;
    static int possible_algarisms[10] = {0,1,2,3,4,5,6,7,8,9};
    srand(std::chrono::system_clock::now().time_since_epoch().count()); 
    int i;
    int arr[13];
    long long code=0;

   /*for(int x=0;x<13;x++){
    i = (rand()%6)+1;
    arr[x]=i;
   }

   for (unsigned y = 0; y < sizeof arr / sizeof arr [0]; ++y)
        ss << arr [y];

   ss>>code;  */

   code=(rand() % 1000000000000) + 1000000000000;     

    //cout << code << endl;

return code;
 }

 std::vector<product_data> readFile(std::string file_name){
    // std::vector<product_data> items={};
   // std::ofstream item_records("item_records.txt");
   // std::ofstream j_ocurrences("j_ocurrences.txt");

   product_data product;
   std::vector<product_data> items;

   FILE* pfile;

   pfile = fopen (file_name.c_str(),"r");

  char value;
  int current_position=0;
  std::string linecontent="";
  vector<std::string> lineContentVector={};
  vector<std::string> productDescription={};
  vector<double> unitaryPrices={};
  vector<double> IVA_increase={};
  vector<long long> ENA13_codes={};
  int separatorOccurrences=0;
   try{
        while((value = fgetc(pfile))!= EOF){
            current_position++;
            linecontent+=value;
            if(value =='\n'){
                lineContentVector.push_back(linecontent);
                linecontent="";
                //line_breaks.push_back(current_position);

            }

        }

    }catch(std::bad_alloc & exception){
        std::cerr << "Bad Alloc Exception" << exception.what();
    }

    lineContentVector.push_back(linecontent);

   fclose(pfile);

   int first_ocurrence_index=0;
   int second_occurrence_index=1;
   int third_occurrence_index=2;
   string second_occurence_value="";
   string third_occurrence_value="";
   for(int i=0;i<lineContentVector.size();i++){
  //  cout << lineContentVector[i] << endl;
   // cout << lineContentVector[i].find(',') << endl;
   separatorOccurrences=0;
   first_ocurrence_index=0;
   second_occurrence_index=0;
   for(int j=0;j<lineContentVector[i].length();j++){
    if(lineContentVector[i].at(j)==','){
        separatorOccurrences++;
        //cout << lineContentVector[i].at(j-1) << endl;
        if(separatorOccurrences==1){
          productDescription.push_back(lineContentVector[i].substr(0,j));
          first_ocurrence_index=j;
        }
        if(separatorOccurrences==2){
          // unitaryPrices.push_back(stod(lineContentVector[i].substr(first_ocurrence_index,j)));
         second_occurence_value=lineContentVector[i].substr(first_ocurrence_index+1,j);
         //cout << second_occurence_value.substr(0,second_occurence_value.find(',')) << endl;
         unitaryPrices.push_back(stod(second_occurence_value.substr(0,second_occurence_value.find(','))));
         second_occurrence_index=j;
        }
        if(separatorOccurrences==3){
          // IVA_increase.push_back(stod(lineContentVector[i].substr(second_occurence_index,j)));
          //cout <<  lineContentVector[i].substr(second_occurrence_index+1,j-1) << endl;
          third_occurrence_value=lineContentVector[i].substr(second_occurrence_index+1,j-1);
         // cout << third_occurrence_value.substr(0,third_occurrence_value.find(',')) << endl; 
          IVA_increase.push_back(stod(third_occurrence_value.substr(0,third_occurrence_value.find(','))));         
        }
    }
   }
    //productDescription.push_back(lineContentVector[i].substr(0,lineContentVector[i].find(',')));
    
   }

   /*for(int j=0;j<productDescription.size();j++){
       cout << productDescription[j] << ", Preco: " << unitaryPrices[j] << ", IVA: " << IVA_increase[j] << endl;
   }*/

  for(int i=0;i<productDescription.size();i++){
    ENA13_codes.push_back(generateEAN13code());
  }

  //cout << "first: " << productDescription[productDescription.size()-1] << endl;
  
  //cout << ENA13_codes.size() << endl;
  /*sort(ENA13_codes.begin(),ENA13_codes.end());
  auto it = unique(ENA13_codes.begin(), ENA13_codes.end());
  ENA13_codes.erase(it, ENA13_codes.end());  
  cout << ENA13_codes.size() << endl;*/

  for(int j=0;j<productDescription.size();j++){
     items.push_back({productDescription[j],unitaryPrices[j],IVA_increase[j],ENA13_codes[j]});
  }

  return items;

 }

  void write_EANcodes_in_File(std::string file_name,std::vector<product_data> items){
     std::fstream store_file(file_name.c_str());
     std::string out_file_name=file_name.substr(0,file_name.length()-3);
     cout << "out file: " << out_file_name << endl;
     //out_file_name.append("")
     std::ofstream item_records("output.txt");
     std::string line;
     int x=0;

     while(getline(store_file,line)){
       /* if(!line.empty()){
          item_records << line;
          item_records << items[x].EAN13_code;
        }*/
       item_records << line;
       item_records << items[x].EAN13_code;
       item_records << "\n";
        //item_records << "\n";
        x++;
     }

     store_file.close();
     item_records.close();

     /*std::ofstream ofs;
     ofs.open("Produtos.txt", std::ofstream::out | std::ofstream::trunc);
     ofs.close();*/
     /*if( remove( file_name.c_str() ) != 0 )
       perror( "Error deleting file" );
     else
       puts( "File successfully deleted" );

    rename("output.txt",file_name.c_str());*/


    /* if( std::filesystem::exists( store_file ) ) {
    auto copyOption{std::filesystem::copy_options::update_existing};    
    std::filesystem::copy_file( item_records, store_file, copyOption);
    std::filesystem::remove( item_records );
std::remove(item_records);
} else {
  std::filesystem::rename( item_records , store_file );
}*/



  }

  void writeReceipt(operation_receipt rec){
      cout << "Purchase Receipt on " << rec.store_id <<"." << endl;
      cout << "Receipt Number " << rec.bill_id << endl;
      cout << "Products bought " << endl;
      //cout << "Name           Price         IVA" << endl;
      printf("%-50s%", "Name");
      printf("%-10s%", "Price");
      printf("%-4s%", "IVA");
      printf("\n");
      
      for(int i=0;i<rec.products_bought.size();i++){
        cout << rec.products_bought[i].description << " " << rec.products_bought[i].unitary_price << " " << rec.products_bought[i].iva << endl;
      }
      cout << "Payments received :" << endl;
      /*if(rec.pt==Cash){
      cout << "Payments received by Cash :" << endl;
      }
      else if(rec.pt==Card){
      cout << "Payments received by Card :" << endl;
      }
      if(rec.pt==MB_WAY){
      cout << "Payments received by MBWay :" << endl;
      }*/
      for(int j=0;j<rec.received_payments.size();j++){
        cout << rec.received_payments[j] << endl;
      }
      
  }

  void writeReceiptinFile(std::string file_name,operation_receipt rec){
     std::ofstream receiptFile;
     receiptFile.open(file_name.c_str(),ofstream::app);
     
     receiptFile << "Purchase Receipt on " << rec.store_id <<"." << endl;
     receiptFile << "Receipt Number " << rec.bill_id << endl;
     receiptFile << "Products bought " << endl;
      //cout << "Name           Price         IVA" << endl;
      printf("%-50s%", "Name");
      printf("%-10s%", "Price");
      printf("%-4s%", "IVA");
      printf("\n");
      for(int i=0;i<rec.products_bought.size();i++){
        receiptFile << rec.products_bought[i].description << " " << rec.products_bought[i].unitary_price << " " << rec.products_bought[i].iva << endl;
      }
       receiptFile << "Payments received :" << endl;
      //receiptFile << "Payments received by " << rec.pt << " :" << endl;
      for(int j=0;j<rec.received_payments.size();j++){
        receiptFile << rec.received_payments[j] << endl;
      }

      receiptFile << endl;
      receiptFile << endl;

  }

  vector<product_data> product_Register_Process(vector<product_data> product_repository){
    double product_to_buy;
   int product_available=0;
   double price;
   vector<product_data> products_registered={};
//Purchase process
    while(product_to_buy!=-1){
      cin >> product_to_buy;
      for(int i=0;i<product_repository.size();i++){
        if(product_repository[i].EAN13_code==product_to_buy){
          products_registered.push_back(product_repository[i]);
          //products_in_store.remove(i);
          price+=product_repository[i].unitary_price;
          cout << "purchase_price: " << price << endl;
          product_available=1;
          product_repository.erase(product_repository.begin()+i);
        }
      }

      if(product_available==0){
          cout << "Product not available. Please insert another EAN13 code." << endl;
        }
        product_available=0;

    }
    return products_registered;
  }

  vector<double> processPayment(vector<product_data> processed_products,double price){
     string payment_str;

     Payment_Type payment;

   double cash_pay_value=0;
   double cash_payed_value=0;
   double change=0;
   vector<double> payment_values={};
   int payment_operation_completion=0;
  //while(payment==Invalid_Payment_Option){
   cout << "Select payment type (Cash,Card or MBWAY): ";
   cin >> payment_str;
   payment=resolvePaymentType(payment_str);
if(payment==Invalid_Payment_Option){
  while(payment==Invalid_Payment_Option){
    cout << "Select payment type (Cash,Card or MBWAY): ";
    cin >> payment_str;
    payment=resolvePaymentType(payment_str);
  }
}
  //}
if(payment!=Invalid_Payment_Option){
 while(payment_operation_completion==0){ 
    if(payment==Cash){
      cout << "Enter the amount of money to submit: ";
      cin >> cash_pay_value;
      if(cash_pay_value+cash_payed_value<price){
        cout << "Cash value is not enough to complete the purchase operation. Please submit an extra " << price-(cash_payed_value+cash_pay_value) << " ." << endl;
        cash_payed_value+=cash_pay_value;
        if(cash_pay_value>0){
        payment_values.push_back(cash_pay_value);
        }
      } 
      else if(cash_pay_value+cash_payed_value>=price){
        cout << "Purchase operation completed. Change is " << (cash_pay_value+cash_payed_value)-price << " ." << endl;
        payment_values.push_back(cash_pay_value);
        payment_operation_completion=1;
      }     
    }
    else if(payment==Card){
         cout << "Card payment processed with the value of " << price << " ." << endl;
         payment_values.push_back(price);
         payment_operation_completion=1;
    }
    else if(payment==MB_WAY){
         cout << "MB_WAY payment processed with the value of " << price << " ";
         payment_values.push_back(price);
         payment_operation_completion=1;
    }
   }

  }
  cash_payed_value=0;

  return payment_values;
 
  }

 
 int main(int argc,char** argv){
    
    int value;
    int endpayment=0;
    char code=' ';
    product_data product;
  
    vector<product_data> products_to_purchase={};
    vector<product_data> products_in_store={};
    double purchase_price=0;
    long long EAN13_c;
    operation_data x;
    string id;
    int id_bill=0;
    vector<operation_receipt> op_receipt_vector={};
    std::string infile="";
    infile=argv[argc-1];


  
    Payment_Type payment;
    remove("receipt.txt");

    menu();
    //scanf("%d",value);
    //cin >> value;
    //scanf("%c",code);

    products_in_store=readFile(infile);

    write_EANcodes_in_File(infile,products_in_store);
    id=infile.substr(0,infile.size()-3);
    cin >> value;
   while(value==1){
    cin >> value;
    if(value==2){
      break;
    }

   // while(code!='e'){
     //if(value==1){
     //Wiating for code to exit register service
     //cin >> code;
     //cout << code << endl;
    // cin >> EAN13_c;
    //cout << EAN13_c << endl;
        
       // }

     //scanf("%lld",&EAN13_c);
     
     //printf("%lld\n",EAN13_c);
     
     /*vector<product_data>::iterator ptr; 
     for(ptr = products_in_store.begin(); ptr < products_in_store.end(); ptr++){
        if(ptr->EAN13_code==EAN13_c){
            ptr=products_in_store.erase(ptr);
        }*/
     
     //for(int i=0;i<products_in_store.size();i++){
        /*if(products_in_store[i].EAN13_code==EAN13_c){
            products_in_store.erase(products_in_store[i]);
        }*/
     //}

     /*for(int i=0;i<products_in_store.size();i++){
        printf("%lld\n",products_in_store[i].EAN13_code);
     }*/

     //generateEAN13code();

    // readFile("Produtos.txt");



    long long product_to_buy=0;


    /*for(int i=0;i<products_in_store.size();i++){
      cout << i << ": " << products_in_store[i].EAN13_code << endl;
    }*/


 //Payment Process
    //cin >> payment;

    products_to_purchase=product_Register_Process(products_in_store);

    for(int i=0;i<products_to_purchase.size();i++){
      purchase_price+=products_to_purchase[i].unitary_price;
    }

    //cout << "Size: " <<  products_to_purchase.size() << endl;

  

 //Update Stock
 ofstream tmp("temp.txt");
 for(int i=0;i<products_in_store.size();i++){
    tmp << products_in_store[i].description << "," << to_string(products_in_store[i].unitary_price) << "," << to_string(products_in_store[i].iva) << "," << to_string(products_in_store[i].EAN13_code) << endl;
 }
 tmp.close();
 remove("output.txt");
 rename("temp.txt","output.txt");
 //products_to_purchase.push_back(products_in_store[i]);
 vector<double> payments={};

 payments=processPayment(products_to_purchase,purchase_price);
 
  //cash_payed_value=0;

  operation_receipt receipt={id,products_to_purchase,payments,id_bill++};
  
  op_receipt_vector.push_back(receipt);

  writeReceipt(receipt);

  }

//Write Receipts in Aux File
for(int i=0;i<op_receipt_vector.size();i++){
  writeReceiptinFile("receipt.txt",op_receipt_vector[i]);
}

    return 0;
 }

 