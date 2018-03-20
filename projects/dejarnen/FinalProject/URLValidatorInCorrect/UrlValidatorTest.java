

import junit.framework.TestCase;
import java.util.Random;


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   System.out.println("Manual Testing...");
	   //String[] schemes = {"http", "https"};
	   UrlValidator value = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // all values should return true
	   System.out.println("True tests...");
	   System.out.println(value.isValid("http://www.google.com"));
	   System.out.println(value.isValid("http://www.google.com/testpath"));
	   System.out.println(value.isValid("http://www.google.com:65535/")); // bug
	   System.out.println(value.isValid("http://www.google.com:6553")); // bug
	   System.out.println(value.isValid("http://www.google.com:655/")); // bug
	   System.out.println(value.isValid("http://www.google.com:65")); // bug
	   System.out.println(value.isValid("http://www.google.com:6/")); // bug
	   System.out.println(value.isValid("http://www.google.com:0")); // bug
	   System.out.println(value.isValid("http://www.google.com/path?view=port"));
	   System.out.println(value.isValid("http://255.255.255.255"));
	   //System.out.println(value.isValid("ftp://www.google.com")); // causes error
	   //System.out.println(value.isValid("https://www.google.com:500/path")); // causes error
	   //System.out.println(value.isValid("https://www.google.com")); // causes error
	   
	   // all values should return false
	   System.out.println("False tests...");
	   System.out.println(value.isValid("://www.google.com"));
	   System.out.println(value.isValid("www.google.com"));
	   System.out.println(value.isValid("http://www.google.com:65999/"));
	   System.out.println(value.isValid("http://www.google.com/.."));
	   System.out.println(value.isValid("http://www.google.com/test//path"));
	   System.out.println(value.isValid("http://////www.google.com"));
	   System.out.println(value.isValid("http://300.300.300.300")); // bug
	   System.out.println(value.isValid("http://bad/Host")); // bug
	   System.out.println(value.isValid("http://www.go/ogle")); // bug
	   //System.out.println(value.isValid("htt://www.google.com")); // causes error
	   
	   // allow 2 slashes
	   UrlValidator newValue = new UrlValidator(UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("Allow 2 slashes test...");
	   System.out.println(newValue.isValid("http://www.google.com/path//testing")); // bug
	   System.out.println(newValue.isValid("http://www.google.com:1500/path//newPath")); // bug
   }
   
   
   public void testYourFirstPartition()
   {
	   String[] correctPartition = {"http", "https", "ftp"};
       String[] incorrectPartition = {"htt", "htts", "ftrp"};
      
       UrlValidator urlValidator = new UrlValidator();
       
       System.out.println("First partition testing...Schemes");
    
       for(int i = 0; i < 3; i++) {
           if (urlValidator.isValidScheme(correctPartition[i])) {
                  System.out.println("url is valid");
               } else {
                  System.out.println("url is invalid");
               }
       }
      
       for(int i = 0; i < 3; i++) {
           if (urlValidator.isValidScheme(incorrectPartition[i])) {
                  System.out.println("url is valid");
               } else {
                  System.out.println("url is invalid");
               }
       }
   }
   
   public void testYourSecondPartition()
   {
	   String[] correctPartition = {"/test1", "/t123", "/$23"};
       String[] incorrectPartition = {"/..", "/../", "/#"}; 
      
       UrlValidator urlValidator = new UrlValidator();
       
       System.out.println("Second partition testing...Paths");
      
       for(int i = 0; i < 3; i++) {
           if (urlValidator.isValidPath(correctPartition[i])) {
               System.out.println("url is valid");
           } else {
               System.out.println("url is invalid");
           }
       	}

      
       for(int i = 0; i < 3; i++) {
           if (urlValidator.isValidPath(incorrectPartition[i])) {
               System.out.println("url is valid");
           } else {
               System.out.println("url is invalid");
           }
       	}
   }
   
   public void testIsValid()
   {
	   UrlValidator newUrl = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String urlString = "";
	   Random rand = new Random();
	   int trueFails = 0;
	   int falseFails = 0;
	   
	   for(int i = 0; i < 1000; i++) {
		   int randauth = rand.nextInt(5);
		   int randport = rand.nextInt(5);
		   int randpath = rand.nextInt(3);
		   int randquery = rand.nextInt(3);
		   int randscheme = rand.nextInt(1);
		   int randport2 = rand.nextInt(3);
		   int randpath2 = rand.nextInt(3);
		   
		   urlString = trueSchemes[randscheme].item + trueAuthority[randauth].item + truePort[randport].item +
				   truePath[randpath].item + query[randquery].item;
		   
		   if(newUrl.isValid(urlString) != true) {
			   trueFails++;
			   System.out.println("TRUE TEST FAILED: " + urlString);
		   }
		   
		   urlString = falseSchemes[randscheme].item + falseAuthority[randauth].item + falsePort[randport2].item +
				   falsePath[randpath2].item + query[randquery].item;
		   
		   if(newUrl.isValid(urlString) != false) {
			   falseFails++;
			   System.out.println("FALSE TEST FAILED: " + urlString);
		   }
		   
	   }
	   System.out.println("Number of true test fails: " + trueFails);
	   System.out.println("Number of false test fails: " + falseFails);
   }
   
   // result pair schemes for testing isValid
   ResultPair[] trueSchemes = {
		   new ResultPair("http://", true),
		   //new ResultPair("", true)
   };
   
   ResultPair[] falseSchemes = {
		   new ResultPair("://", false),
		   new ResultPair("//:", false)
   };
   
   ResultPair[] trueAuthority = {
		   new ResultPair("www.google.com", true),
		   new ResultPair("google.com", true),
		   new ResultPair("www.google.au", true),
		   new ResultPair("255.255.255.255", true),
		   new ResultPair("test.com", true)
   };
   
   ResultPair[] falseAuthority = {
		   new ResultPair("ggg", false),
		   new ResultPair("299.299.299.299", false),
		   new ResultPair("google.", false),
		   new ResultPair(".google", false),
		   new ResultPair("", false)
   };
   
   ResultPair[] truePort = {
		   new ResultPair("", true),
		   new ResultPair(":0", true),
		   new ResultPair(":65", true),
		   new ResultPair(":655", true),
		   new ResultPair(":6553", true),
		   new ResultPair(":65535", true)
   };
   
   ResultPair[] falsePort = {
		   new ResultPair(":-10", false),
		   new ResultPair(":65536", false),
		   new ResultPair(":100a", false)
   };
   
   ResultPair[] truePath = {
		   new ResultPair("/path", true),
		   new ResultPair("/path/path2", true),
		   new ResultPair("/$test/", true),
		   new ResultPair("", true)
   };
   
   ResultPair[] falsePath = {
		   new ResultPair("/..", false),
		   new ResultPair("/../", false),
		   new ResultPair("/path//path", false)
   };
   
   ResultPair[] query = {
		   new ResultPair("", true),
		   new ResultPair("?mode=view", true),
		   new ResultPair("?mode=view&action=go", true)
   };

}
