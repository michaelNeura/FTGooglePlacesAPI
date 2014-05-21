//
//  FTGooglePlacesAPIAutocompleteRequest.m
//  Pods
//
//  Created by Yuva on 5/20/14.
//
//

#import "FTGooglePlacesAPIAutocompleteRequest.h"

static const NSUInteger kMinOffset = 1;

static const NSUInteger kDefaultRadius = 20000000;

static CLLocationCoordinate2D kDefaultLocation;

/**
 *  Private methods interface
 */
@interface FTGooglePlacesAPIAutocompleteRequest (Private)

- (NSString *)gpacr_nameOfPlaceTypeByParam:(FTGooglePlacesAPIAutocompletePlaceType)placeByParam;

@end

#pragma mark -

@implementation FTGooglePlacesAPIAutocompleteRequest

#pragma Lifecycle

- (instancetype)initWithSearchText:(NSString *)searchText
{
    //  Validate searchText
    
    if ([searchText isEqual:[NSNull null]] || searchText==nil) {
     
        NSLog(@"WARNING: %s: SearchText:%@ is nil, returning nil", __PRETTY_FUNCTION__, searchText);
        
        return nil;
    }
    
    self = [super init];
    
    if (self) {
        
        _input = searchText;
        
        kDefaultLocation = CLLocationCoordinate2DMake(0, 0);
        
        _language = [[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode];
        
        _components = [[NSLocale currentLocale] objectForKey:NSLocaleCountryCode];
        
    }
    return self;
}

#pragma mark Accessors

- (void)setRadius:(NSUInteger)radius
{
    [self willChangeValueForKey:@"radius"];
    
    //  Validate radius
    _radius = radius;
    
    [self didChangeValueForKey:@"radius"];
}

- (void)setOffset:(NSUInteger)offset
{
    [self willChangeValueForKey:@"offset"];
    
    //  value ranges 1 to searchText length
    _offset = MAX(kMinOffset,MIN(_input.length, offset));
    
    [self didChangeValueForKey:@"offset"];
}

- (void)setLocationCoordinate:(CLLocationCoordinate2D)locationCoordinate
{
    [self willChangeValueForKey:@"locationCoordinate"];
    
    if (!CLLocationCoordinate2DIsValid(locationCoordinate)) {
        
        NSLog(@"WARNING: %s: Location (%f, %f) is invalid, returning nil", __PRETTY_FUNCTION__, locationCoordinate.latitude, locationCoordinate.longitude);
        
        _locationCoordinate = kDefaultLocation;
        
        _radius = kDefaultRadius;
    }
    
    [self didChangeValueForKey:@"locationCoordinate"];
}

#pragma mark Superclass overrides

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@: %p> %@", [self class], self, [self placesAPIRequestParams]];
}

#pragma mark FTGooglePlacesAPIRequest protocol

- (NSString *)placesAPIRequestMethod
{
    return @"autocomplete";
}

- (NSDictionary *)placesAPIRequestParams
{
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    
    //  Required parameters
    
    params[@"input"] = _input;
    
    //  Optional parameters
    
    if(_offset>0)
        params[@"offset"] = [NSString stringWithFormat:@"%ld",(unsigned long)_offset];
    
    if(CLLocationCoordinate2DIsValid(_locationCoordinate))
        params[@"location"] = [NSString stringWithFormat:@"%.7f,%.7f", _locationCoordinate.latitude, _locationCoordinate.longitude];
    
    if (_radius >0)
        params[@"radius"] = [NSString stringWithFormat:@"%ld", (unsigned long)_radius];

    if (_language)
        params[@"language"] = _language;
    
    NSString *types = [self gpacr_nameOfPlaceTypeByParam:_types];
    
    if (types)
        params[@"types"] = types;
    
    if (_components)
        params[@"components"] = [NSString stringWithFormat:@"country:%@",_components];
    
    return [params copy];
}

@end

#pragma mark - Private methods category

@implementation FTGooglePlacesAPIAutocompleteRequest (Private)

- (NSString *)gpacr_nameOfPlaceTypeByParam:(FTGooglePlacesAPIAutocompletePlaceType)placeByParam
{
    NSString *name = nil;
    
    switch (placeByParam)
    {
        case FTGooglePlacesAPIAutocompletePlaceTypeGeocode:
            name = @"geocode";
            break;
        case FTGooglePlacesAPIAutocompletePlaceTypeEstablishment:
            name = @"establishment";
            break;
        case FTGooglePlacesAPIAutocompletePlaceTypeRegions:
            name = @"(regions)";
            break;
        case FTGooglePlacesAPIAutocompletePlaceTypeCities:
            name = @"(cities)";
            break;
    }
    
    return name;
}

@end
