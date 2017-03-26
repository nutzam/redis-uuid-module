#include "nutzam_uuid.h"

int NutzamUUID_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    uuid_t id;
    uuid_generate(id);
    char* str = (char*)RedisModule_Alloc(36);
    uuid_unparse(id, str);
    RedisModuleString *reply_str = RedisModule_CreateString(ctx, str, 36);
    RedisModule_ReplyWithString(ctx, reply_str);
    RedisModule_FreeString(ctx, reply_str);
    RedisModule_Free((void*)str);
    return REDISMODULE_OK;
}

/*
int NutzamUU32_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    uuid_t id;
    uuid_generate(id);
    char* str = (char*)RedisModule_Alloc(26);
    char* uu32 = id;

    RedisModuleString *reply_str = RedisModule_CreateString(ctx, str, 26);
    RedisModule_ReplyWithString(ctx, reply_str);
    return REDISMODULE_OK;
}
*/

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"nutzam.uuid",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"nutzam.uuid",
        NutzamUUID_RedisCommand, "readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    /*
    if (RedisModule_CreateCommand(ctx,"nutzam.uu32",
        NutzamUU32_RedisCommand, "readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    */
    //printf("uu32 sizeof %d\r\n", sizeof(struct nutzam_uu32));
    return REDISMODULE_OK;
}
