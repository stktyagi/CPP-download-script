#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstdlib>

using namespace std;

//write_data function to pass as an arguement to curl_easy_setopt. It provides a refernce to the function about what (binary)data to write in the output file.
//size_t datatype is usually used for sizes and is the return to the sizeof() built-in function. It is the forma required by the curl function. refer this link - https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
size_t write_data(void* ptr, size_t size, size_t nmemb, FILE *fdata){
	size_t written=fwrite(ptr,size,nmemb,fdata);
	return written;
}

//function to download file, takes constant url address and output file address as arguements.
//Almost all of the curl functionality is implemented here.
//For info on functions used refer - https://curl.se/libcurl/c/CURLOPT_URL.html, https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html, https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
//CURLE_OK (zero) means that the option was set properly, non-zero means an error occurred as <curl/curl.h> defines. See the libcurl-errors man page for the full list with descriptions.
bool download_file(const string& url, const string& output_file){
	CURL *curl=curl_easy_init();
	FILE *fp;
	CURLcode res;
	
	if(curl){
		fp = fopen(output_file.c_str(), "wb"); // Open the output file in binary write mode
    // Set options for the libcurl easy handle
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set the URL to download
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // Set the function to write data to file
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Set the file to write data to
		res = curl_easy_perform(curl);
		if(res!=CURLE_OK){
			cout << "curl failed" << curl_easy_strerror(res) << endl;
			fclose(fp);
			curl_easy_cleanup(curl);
			return false;
		}
		fclose(fp);
		curl_easy_cleanup(curl);
		return true;
	}
	return false;
}

/*sample url provided below, most of the time the normal download link should work fine but if you encounter an empty of a less file size than expected then you'll have to use 
curl request of that file from the networks tab. Steps for that - 
1.)Go to the page where the download link is provided.
2.)Open chromo developer tools window and go to the networks tab.
3.)click on download and check for the document on the tab.
4.)right click and copy as curl.
5.)paste the link replacing the sample url.
*/

int main(){
	const string url="https://videos.pexels.com/video-files/4114797/4114797-uhd_3840_2160_25fps.mp4";
	const string output_file="video.mp4";
	curl_global_init(CURL_GLOBAL_DEFAULT);
	bool success = download_file(url,output_file);
	curl_global_cleanup();
	if (success){
		cout << "downloaded";	
	}
	else{
		cout << "failed";
	}
	return 0;
}
