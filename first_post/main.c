#include <stdio.h>
#include <curl/curl.h>
#include <json/json.h>

void start_curl(json_object *json_park);

int main(void)
{

    printf("hello!\n");

    //char *parking = "{\"key\":\"carIsParking\"}";
    char *parking = "{\"key\":\"carIsLeaving\"}";
    json_object *json_park = json_tokener_parse(parking);

    printf("%s\n", json_object_get_string(json_park));

    start_curl(json_park);

    return 0;
}

void start_curl(json_object *json_park) {
    CURL *curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "https://triangela.net/uat/parking/sync.php");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_to_json_string(json_park));
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}