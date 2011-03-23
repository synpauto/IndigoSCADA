//-< TESTPERF.CPP >--------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     10-Dec-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 20-Jan-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Performance test for index and sequential searches
//-------------------------------------------------------------------*--------*

#include <stdio.h>
#include "fastdb.h"

USE_FASTDB_NAMESPACE

const int nRecords = 1000000;
const int nSequentialSearches = 10;

class Record { 
  public:
    char const* key;
    char const* value;

    TYPE_DESCRIPTOR((KEY(key, HASHED|INDEXED), FIELD(value)));
};

REGISTER(Record);


#ifdef VXWORKS
int testperfmain(int argc, char* argv[]) 
#else
int main(int argc, char* argv[]) 
#endif // VXWORKS
{
    int i, n;
    int nThreads = 1;
    char buf[32];

    if (argc > 1) { 
        nThreads = atoi(argv[1]);
    }
    dbDatabase db;
    if (db.open(_T("testperf"))) { 
        db.setConcurrency(nThreads);
        nat8 key = 1999;
        time_t start = time(NULL);
        for (i = 0; i < nRecords; i++) { 
            Record rec;
            key = (3141592621u*key + 2718281829u) % 1000000007u;
            sprintf(buf, INT8_FORMAT ".", key);
            rec.key = buf;
            rec.value = buf;
            insert(rec);
        }
        printf("Elapsed time for inserting %d record: %d seconds\n", 
               nRecords, int(time(NULL) - start));
        start = time(NULL);
        db.commit();
        printf("Commit time: %d\n", int(time(NULL) - start));
db.close();
return 0;
        dbQuery q;
        dbCursor<Record> cursor;

        q = "key=",buf;
        start = time(NULL);
        key = 1999;
        for (i = 0; i < nRecords; i++) { 
            key = (3141592621u*key + 2718281829u) % 1000000007u;
            sprintf(buf, INT8_FORMAT ".", key);
            n = cursor.select(q);
            assert(n == 1);
        }
        printf("Elapsed time for %d hash searches: %d seconds\n", 
               nRecords, int(time(NULL) - start));
        q = "key like",buf;
        start = time(NULL);
        key = 1999;
        cursor.setSelectionLimit(1);
        for (i = 0; i < nRecords; i++) { 
            key = (3141592621u*key + 2718281829u) % 1000000007u;
            sprintf(buf, INT8_FORMAT ".%%", key);
            n = cursor.select(q);
            assert(n == 1);
        }
        printf("Elapsed time for %d index searches: %d seconds\n", 
               nRecords, int(time(NULL) - start));
        q = "value=key";
        cursor.unsetSelectionLimit();
        start = time(NULL);
        for (i = 0; i < nSequentialSearches; i++) { 
            n = cursor.select(q);
            assert(n == nRecords);
        }
        printf("Elapsed time for %d sequential search through %d records: "
               "%d seconds\n", nSequentialSearches, nRecords, 
               int(time(NULL) - start));
        
        q = "value=key order by value";
        start = time(NULL);
        n = cursor.select(q);
        assert(n == nRecords);
        printf("Elapsed time for search with sorting %d records: %d seconds\n",
               nRecords, int(time(NULL)-start));
        char const* curr = cursor->key;
        for (i = nRecords; --i != 0;) { 
            char const* succ = cursor.next()->key; 
#ifdef USE_LOCALE_SETTINGS
            assert(strcoll(succ, curr) > 0); 
#else
            assert(strcmp(succ, curr) > 0); 
#endif
            curr = succ;
        }
        start = time(NULL);
        cursor.removeAll();
        printf("Elapsed time for deleting all %d records: %d seconds\n", 
               nRecords, int(time(NULL) - start));
        db.close();
        return EXIT_SUCCESS;
    } else { 
        printf("Failed to open database\n");
        return EXIT_FAILURE;
    }
}




