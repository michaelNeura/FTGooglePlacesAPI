//
//  FTGooglePlacesAPIAutocompleteRequest.h
//  Pods
//
//  Created by Yuva on 5/20/14.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "FTGooglePlacesAPICommon.h"

/**
 *  Class for encapsulating Google Places API "Place Autocomplete" request
 *  See https://developers.google.com/places/documentation/autocomplete
 *
 *  The Place Autocomplete service is a web service that returns place predictions in response 
 *  to an HTTP request. The request specifies a textual search string and optional geographic bounds. 
 *  The service can be used to provide autocomplete functionality for text-based geographic searches, 
 *  by returning places such as businesses, addresses and points of interest as a user types.
 *
 *  FTGooglePlacesAPIAutocompleteRequest and FTGooglePlacesAPITextSearchRequest
 *  have a lot of the same code. They don't have the common superclass
 *  (and so have copied code) to make them totaly standalone.
 *  We don't have any quarantee the single concrete request won't change
 *  in the future (keys dependency or exclusivity etc.) and shared common
 *  code and properties could cause a lot of trouble in that case
 */

/**
 *  @see type
 */
typedef NS_ENUM(NSUInteger, FTGooglePlacesAPIAutocompletePlaceType) {
    /**
     *  This option instructs the Place Autocomplete service to return only geocoding (address) results. 
     *  Generally, you use this request to disambiguate results where the location specified may be indeterminate..
     */
    FTGooglePlacesAPIAutocompletePlaceTypeGeocode,
    /**
     *  This option instructs the Place Autocomplete service to return only business results.
     */
    FTGooglePlacesAPIAutocompletePlaceTypeEstablishment,
    /**
     *  This (regions) type collection instructs the Places service to return any result matching 
     *  the following types:
     *  locality
     *  sublocality
     *  postal_code
     *  country
     *  administrative_area1
     *  administrative_area2
     */
    FTGooglePlacesAPIAutocompletePlaceTypeRegions,
    /**
     *  This (cities) type collection instructs the Places service to return results that match either
     *  locality or administrative_area3.
     */
    FTGooglePlacesAPIAutocompletePlaceTypeCities
};


@interface FTGooglePlacesAPIAutocompleteRequest : NSObject <FTGooglePlacesAPIRequest>

//  Required parameters

/**
 *  The text string on which to search. The Place Autocomplete service will return candidate 
 *  matches based on this string and order results based on their perceived relevance.
 */
@property (nonatomic, copy) NSString *input;

/*
 *  Optional parameters
 *  See https://developers.google.com/places/documentation/autocomplete for detailed descriptions
 */

/**
 *  The position, in the input term, of the last character that the service uses to match predictions. 
 *  For example, if the input is 'Google' and the offset is 3, the service will match on 'Goo'. 
 *  The string determined by the offset is matched against the first word in the input term only. 
 *  For example, if the input term is 'Google abc' and the offset is 3, the service will attempt to 
 *  match against 'Goo abc'. If no offset is supplied, the service will use the whole term. 
 *  The offset should generally be set to the position of the text caret.
 */
@property (nonatomic, assign) NSUInteger offset;

/**
 *  The latitude/longitude around which to retrieve Place information.
 *  Property is read-only, value is set in init method
 */
@property (nonatomic, assign) CLLocationCoordinate2D locationCoordinate;


/**
 *  The distance (in meters) within which to return place results. Note that setting a radius biases 
 *  results to the indicated area, but may not fully restrict results to the specified area.
 */
@property (nonatomic, assign) NSUInteger radius;

/**
 *  The language code, indicating in which language the results should be returned, if possible.
 *  See http://spreadsheets.google.com/pub?key=p9pdwsai2hDMsLkXsoM05KQ&gid=1 for a complete list
 *
 *  Default value is determined by active application language from NSUserDefaults
 *  if available
 *  (details: https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/Articles/ChoosingLocalizations.html)
 */
@property (nonatomic, copy) NSString *language;

/**
 *  The types of place results to return.
 */
@property (nonatomic, assign) FTGooglePlacesAPIAutocompletePlaceType types;

/**
 *  A grouping of places to which you would like to restrict your results. Currently,
 *  you can use components to filter by country. The country must be passed as a two character,
 *  ISO 3166-1 Alpha-2 compatible country code. For example: components=country:fr would restrict
 *  your results to places within France.
 */
@property (nonatomic, copy) NSString *components;


/**
 *  Creates new intance of Places API request.
 *
 *  @param searchText The text string on which to search. The Place Autocomplete service will return 
 *  candidate matches based on this string and order results based on their perceived relevance. 
 *  This stands for "input" Google Places API parameter
 *
 *  @return Request instance. If the provided searchText are null, returns nil
 */
- (instancetype)initWithSearchText:(NSString *)searchText;

@end
