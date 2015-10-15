#pragma once
#include "gen/MX3Http.h"

@interface MX3HttpObjc : NSObject <MX3Http>

- (void)get:(NSString *)url
    headers:(NSDictionary *)headers
   callback:(MX3HttpCallback *)callback;

- (void)post:(NSString *)url
        body:(NSString *)body
     headers:(NSDictionary *)headers
    callback:(MX3HttpCallback *)callback;

@end
