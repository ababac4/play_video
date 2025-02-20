#ifndef CREDIS_H
 #define CREDIS_H
 #include<iostream>
 #include<hiredis/hiredis.h>
 #include<list>
 using namespace  std;
 #define DEF_REDIS_IP  "127.0.0.1"
 #define DEF_REDIS_PORT  6379
 #define DEF_BUFF_SIZE   200
 class CRedis
 {
 public:
    CRedis(const char* ip = DEF_REDIS_IP , unsigned int port = DEF_REDIS_PORT );
    ~CRedis();
 public:

    bool isExist( const string&  key );
    void removeKey( const string&  key);
    bool grepKeys(const string&  key,list<string>&vals);
    bool setEmire(const string&  key,int second);
    ///string
    bool setString( const string& key , const string& val);
    bool getString( const string& key , string& val ); //能否取出用bool返回
    bool setex( const string& key , const string& val,int second);
    ///list
    bool setList( const string& key , list<string> &val );// 设置多个value
    bool appendOneToList( const string& key , const string& val);
    bool getList( const string& key , list<string> &val );
    bool Remvals( const string& key , const string &val );
    ///hash
    bool getHashVal(const string& key , const string& field,  string &val);
    bool setHashVal( const string& key , const string& field,  const string& val );
       bool delHashField( const string& key , const string& field );
       bool getHashVals( const string& key , list<string>& field,  list<string> &val);
       bool setHashVals( const string& key , list<string>& field,  list<string> &val );
       bool hvals(const string& key, list<string> &vals);
       bool hgetall(const string& key,list<string>& field,  list<string> &val);
       ///set
       bool appondOneToSet( const string& key , const string& val );
       bool getSetVals( const string& key , list<string> &vals);
       bool delSetVal( const string& key , const string& val );
       ///zset
       bool appondOneToZSet(const string& key , const string& val , int score);
       bool getZSetVals( const string& key , list<string> &vals);
       bool getZSetValsByScore(const string& key , list<string> &vals , int minScore , int maxScore);
       bool delZSetVal( const string& key , const string& val );
       bool delZSetValByScore( const string& key , const string& val , int minScore , int maxScore);
    private:
       void init();
       redisReply* command( const char * str );
       string m_ip;
       unsigned int m_port;
       redisContext * m_redis;
    };
  #endif // CREDIS_H
