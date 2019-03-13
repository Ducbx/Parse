// Example program
#include <iostream>
#include <string>
using namespace std;

enum ParseState
{
    STATE_NONE=0,
    SELECT_S,
    SELECT_SE,
    SELECT_L,
    SELECT_LE,
    SELECT_C,
    SELECT_T,
    SPACE_AFTER_SELECT,
    STATE_FIELD_NAME,
    SPACE_AFTER_FIELD,
    FROM_F,
    FROM_R,
    FROM_O,
    FROM_M,
    SPACE_AFTER_FROM,
    STATE_TABLE_NAME
};

struct QueryStruct
{
    string tableName;
    string fieldName;
};
typedef struct QueryStruct QUERYSTRUCT;

bool parse(const string str, QUERYSTRUCT& query)
{
    ParseState state=STATE_NONE;
    int len = str.length();
    for(int i=0;i<len;++i)
    {
        switch(state)
        {
            case STATE_NONE:
                if(str[i]=='S')
                {
                    state = SELECT_S;
                }
                else
                {
                    cout<<"expected S but got "<<str[i];
                    return false; 
                }
                break;
            case SELECT_S:
                if(str[i]=='T')
                {
                    state = SELECT_T;
                }
                else
                {
                    cout<<"expected T but got "<<str[i];
                    return false; 
                }
                break;
                /* ... */
            case SELECT_T:
                if(str[i]==' ')
                {
                    state = SPACE_AFTER_SELECT;
                }
                else
                {
                    cout<<"expected SPACE but got "<<str[i];
                    return false; 
                }
                break;
            case SPACE_AFTER_SELECT:
            case STATE_FIELD_NAME:
                if(str[i]==' ')
                {
                    state = SPACE_AFTER_FIELD;
                }
                else
                {
                    query.fieldName += str[i];
                    state = STATE_FIELD_NAME;
                }
                break;
            case SPACE_AFTER_FIELD:
                if(str[i]=='F')
                {
                    state = FROM_F;
                }
                else
                {
                    cout<<"expected F but got "<<str[i];
                    return false; 
                }
                break;
            /* --- */
            case FROM_F:
                if(str[i]=='M')
                {
                    state = FROM_M;
                }
                else
                {
                    cout<<"expected M but got "<<str[i];
                    return false; 
                }
                break;
            case FROM_M:
                if(str[i]==' ')
                {
                    state = SPACE_AFTER_FROM;
                }
                else
                {
                    cout<<"expected SPACE but got "<<str[i];
                    return false; 
                }
                break;
            case SPACE_AFTER_FROM:
            case STATE_TABLE_NAME:
                query.tableName += str[i];
                state = STATE_TABLE_NAME;
                break;
            default:
                cout<<"invalid state";
                break;
        }
    }
    return true;
}

int main()
{
    string str="ST buixuanduc FM vymanhcuong";
    QueryStruct res;
    if( parse(str,res) )
    {
        cout<<"Field name: "<<res.fieldName<<endl;
        cout<<"Table name: "<<res.tableName<<endl;
    }
    system("pause");
    return 0;
}
