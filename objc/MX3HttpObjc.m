#include <Foundation/Foundation.h>
#include "MX3HttpObjc.h"
#include "gen/MX3HttpCallback.h"

@implementation MX3HttpObjc

- (void) get:(NSString *)urlString headers:(NSDictionary *)headers callback:(MX3HttpCallback *)callback {
    NSURL *URL = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:URL];

    [self SetupHeaders:headers request:request];
    
    [[[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            [callback onNetworkError];
        } else {
            int16_t httpCode = [(NSHTTPURLResponse*) response statusCode];
            NSString * strData = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            [callback onSuccess:httpCode data: strData];
        }
    }] resume];
}

- (void)post:(nonnull NSString *)url body:(nonnull NSString *)body headers:(nullable NSDictionary*)headers callback:(nullable MX3HttpCallback *)callback
{
    NSURL *URL = [NSURL URLWithString:url];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:URL];
    [request setHTTPMethod:@"POST"];
    [request setHTTPBody:[body dataUsingEncoding:NSUTF8StringEncoding]];

    [self SetupHeaders:headers request:request];

    [[[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            [callback onNetworkError];
        } else {
            int16_t httpCode = [(NSHTTPURLResponse*) response statusCode];
            NSString * strData = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            [callback onSuccess:httpCode data: strData];
        }
    }] resume];
}

- (void)SetupHeaders:(NSDictionary *)headers request:(NSMutableURLRequest *)request
{
    if(headers != nil)
    {
        for (NSString *key in headers)
        {
            NSString *header = [headers objectForKey:key];
            NSLog(@"Header Key: %@, Header Value: %@", key, header);
            [request setValue:header forHTTPHeaderField:key];
        }
    }
}

@end
