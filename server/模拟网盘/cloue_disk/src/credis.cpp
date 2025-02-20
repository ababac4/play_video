#include "credis.h"
#include<string.h>
CRedis::CRedis(const char *ip, unsigned int port):
    m_ip(ip),m_port(port),m_redis(nullptr)
{
    init();
}
CRedis::~CRedis()
{
    if( m_redis ){redisFree( m_redis );
        cout << "redis free connect." << endl;
        m_redis = nullptr;
    }
}
void CRedis::init()
{
    //连接redis
    struct timeval tmout ={ 1, 500000 }; //1.5 秒超时时间
    cout << "init ip:" << m_ip.c_str() <<" port:" << m_port << endl;
    m_redis = redisConnectWithTimeout( m_ip.c_str() , m_port, tmout);
    //查看是否有问题
    if( m_redis->err )
    {
        cout << "connect error :" << m_redis->errstr << endl;
    }else{
        cout << "redis connect success!" <<endl ;
    }
    redisReply * reply = nullptr; //请求返回值
    char buf[ DEF_BUFF_SIZE ] = "select 1";

    reply = this->command(buf);

}
redisReply *CRedis::command(const char *str)
{
    redisReply * reply = nullptr; //请求返回值
    if( !m_redis || m_redis->err ){
        cout << "redis init error" <<endl;
        init();
        return reply;
    }
    //请求
    reply = (redisReply*)redisCommand( m_redis , str );
    //返回值 返回出去外面使用
    if( reply ){
        return reply;
    }else{ //command 异常
        redisFree( m_redis );
        m_redis = nullptr;
        cout << str << " error reply = null " <<endl;
        return reply;
    }
}
//REDIS_REPLY响应的类型type
//cout << "#define REDIS_REPLY_STRING 1"<< endl;
//cout << "#define REDIS_REPLY_ARRAY 2"<< endl;
//cout << "#define REDIS_REPLY_INTEGER 3"<< endl;
//cout << "#define REDIS_REPLY_NIL 4"<< endl;
//cout << "#define REDIS_REPLY_STATUS 5"<< endl;
//cout << "#define REDIS_REPLY_ERROR 6"<< endl;
bool CRedis::isExist(const string & key)
{
    redisReply * reply = nullptr; //请求返回值
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "exists %s" , key.c_str() );
    reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
void CRedis::removeKey(const string &key)
{
    redisReply * reply = nullptr; //请求返回值
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "del %s" , key.c_str() );
    reply = this->command( buf );
    if( !reply ) return;
    //回收返回值
    freeReplyObject(reply);
    return;
}

bool CRedis::grepKeys(const string &key,list<string>&val)
{

    char buf[ DEF_BUFF_SIZE ] = "";

    sprintf(buf,"keys %s",key.c_str());

    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            val.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::setEmire(const string &key, int second)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "expire %s %d" , key.c_str(),second);
    redisReply *reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::setString(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "set %s %s" , key.c_str() , val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( strcmp( reply->str , "OK") == 0 ) // == ok
    {
        flag = true;
    }else{
        flag = false;
        cout << "set string fail : " << reply->str <<endl;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::getString(const string &key, string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "get %s" , key.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->len > 0 ) //返回结果有多长
    {
        val = reply->str;
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::setex(const string &key, const string &val,int second)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "setex %s %d %s" , key.c_str() ,second,val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( strcmp( reply->str , "OK") == 0 ) // == ok
    {
        flag = true;
    }else{
        flag = false;
        cout << "set string fail : " << reply->str <<endl;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::setList(const string &key, list<string> &val)
{
    //先删除
    removeKey( key );
    //然后设置
    uint ncount = 0 ;
    for( auto ite = val.begin() ; ite != val.end() ;  ++ite )
    {
        if( appendOneToList( key , *ite ) )
            ncount++;
    }
    if( ncount == val.size() )
        return true;
    else
        return false;
}

bool CRedis::appendOneToList(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    snprintf(buf, sizeof(buf), "RPUSH %s %s", key.c_str(), val.c_str());
    //cout<<buf<<endl;
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER ) //返回结果有多长
    {
        if( reply->integer > 0  )
            flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::getList(const string &key, list<string> &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "lrange %s 0 -1" , key.c_str() );
    //cout<<"buf1"<<endl;
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            val.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    //cout<<"buf2"<<endl;
    return flag;
}


bool CRedis::Remvals(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "LREM %s 0 %s" , key.c_str(),val.c_str());
    redisReply *reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::getHashVal(const string &key, const string &field, string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "hget %s %s" , key.c_str() , field.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->len > 0 ) //返回结果有多长
    {
        val = reply->str;
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::setHashVal(const string &key, const string &field, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "hset %s %s %s"
             , key.c_str() , field.c_str() , val.c_str() );
    //先删除再设置
    delHashField( key , field );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::delHashField(const string &key, const string &field)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "hdel %s %s"
             , key.c_str() , field.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) {
        return false;
    }
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::getHashVals(const string &key, list<string> &fields, list<string> &vals)
{
    for( auto ite = fields.begin(); ite != fields.end() ; ++ite ){
        string val = "";
        getHashVal( key , *ite ,val ) ;
        vals.push_back( val );
    }
    return true;
}
bool CRedis::setHashVals(const string &key, list<string> &field, list<string> &val)
{
    if( field.size() != val.size())
    {
        cout<<key<<endl;
        for(auto i:field) cout<<"filed"<<i<<endl;
        for(auto i:val) cout<<"val"<<i<<endl;
        cout << " field size != val size \n";
        return false;
    }
    auto iteField = field.begin() ;
    auto iteVal = val.begin();
    for( ; iteField != field.end()&& iteVal != val.end() ; ++iteField , ++iteVal)
    {
        if( !setHashVal( key ,*iteField , *iteVal ) ){
            removeKey( key );
            return false;
        }
    }
    return true;
}

bool CRedis::hvals(const string &key, list<string> &vals)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "hvals %s" , key.c_str());
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            vals.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::hgetall(const string &key, list<string>& field, list<string>& val)
{
    char buf[DEF_BUFF_SIZE] = "";
    sprintf(buf, "hgetall %s", key.c_str());
    redisReply *reply = this->command(buf);
    if (!reply) return false;

    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j += 2) {
            if (j + 1 < reply->elements) { // 确保还有对应的值
                field.push_back(reply->element[j]->str);
                val.push_back(reply->element[j + 1]->str);
                flag = true;
            }
        }
    }

    // 回收返回值
    freeReplyObject(reply);
    return flag;
}



bool CRedis::appondOneToSet(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "sadd %s %s" , key.c_str(), val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER ) //返回结果有多长
    {
        if( reply->integer > 0)
            flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::getSetVals(const string &key, list<string> &vals)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "smembers %s " , key.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            vals.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::delSetVal(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "srem %s %s"
             , key.c_str() , val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}

bool CRedis::appondOneToZSet(const string &key, const string &val , int score)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "zadd %s %d %s" , key.c_str(),  score , val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER ) //返回结果有多长
    {
        if( reply->integer > 0  )
            flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::getZSetVals(const string &key, list<string> &vals)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "zrange %s 0 -1 withscores" , key.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            vals.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::getZSetValsByScore(const string &key, list<string> &vals, int minScore, int maxScore)
{
    //zrangebyscore  playhall 150 250
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf ,"zrangebyscore %s %d %d ", key.c_str() , minScore , maxScore );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (unsigned int j = 0; j < reply->elements; j++) {
            vals.push_back( reply->element[j]->str) ;
        }
        flag = true;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::delZSetVal(const string &key, const string &val)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "zrem %s %s"  , key.c_str() , val.c_str() );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
bool CRedis::delZSetValByScore(const string &key, const string &val, int minScore, int maxScore)
{
    char buf[ DEF_BUFF_SIZE ] = "";
    sprintf( buf , "zremrangebyscore %s %d %d "
             , key.c_str() , minScore , maxScore );
    redisReply * reply = this->command( buf );
    if( !reply ) return false;
    bool flag = false;
    if( reply->type == REDIS_REPLY_INTEGER )
    {
        if( reply->integer > 0 )
            flag = true;
        else
            flag = false;
    }
    //回收返回值
    freeReplyObject(reply);
    return flag;
}
