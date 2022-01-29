/**************************************************

FILE: durations.cc

AUTHOR: Carter Steckbeck

DATE: 1/24/19

DESCRIPTION: Program that takes the number of trips and range of dates for
             trips and outputs the total days, shortest trip, longest trip, and
             average trip duration.
**************************************************/

#include <iostream>
#include <iomanip>

// Function that returns the month in a given date as a string
std:: string get_month(std::string date, int index)
{
  std:: string month = date.substr(0, index);
  return month;
}

// Function that returns the days in the date as a string
std:: string get_days(std::string date, int index)
{
  std:: string days = date.substr(index + 1, date.length());
  return days;
}

// Function that calculates the duration of a trip
int calculate_dur(std::string first_month, std::string first_days,
                  std::string second_month, std::string second_days)
{
  // Converts first_month and second_month to int
  int first_month_num = std::stoi(first_month);
  int second_month_num = std::stoi(second_month);

  // Converts first_days_num and second_days_num to int
  int first_days_num = std:: stoi(first_days);
  int second_days_num = std:: stoi(second_days);

  // Intializes int dur which will represent duration of a given trip
  int dur = 0;

  // Checks if first_days_num is less than second_month_num, then goes into
  // a while loop until this condition is not met
  if (first_month_num < second_month_num) {
    while(first_month_num < second_month_num) {

      // If the first_month_num is a month with 31 days, subtract first_days_num
      // and add that to dur
      if (first_month_num == 1 || first_month_num == 3 ||first_month_num == 5 ||
      first_month_num == 7 || first_month_num == 8 || first_month_num == 10 ||
      first_month_num == 12)
        dur += 32 - first_days_num;

      // If the first_month_num is a month with 30 days, subtract first_days_num
      // and add that to dur
      if(first_month_num == 4 || first_month_num == 6 || first_month_num == 9 ||
        first_month_num == 11)
        dur += 31 - first_days_num;

      // If the first_month_num is a month with 29 days, subtract first_days_num
      // and add that to dur
      if(first_month_num == 2)
        dur += 30 - first_days_num;

      // Increase first_month_num and set first_days_num to 1 to represent
      // first day of next month
      ++first_month_num;
      first_days_num = 1;
    }
  }

  // Computes duration of trip with the days left in the same month, returns it
  dur += second_days_num - first_days_num + 1;
  return dur;
}

// Function that separates the two dates and returns duration of trip
int separate_dates(std::string date_range)
{
  // Finds index of the slash and dash within the date_range
  int slash_index = date_range.find("/");
  int dash_index = date_range.find("-");

  // Finds first_date in date_range
  std::string first_date = date_range.substr(0, dash_index);

  // Identify first_month and first_days
  std::string first_month = get_month(first_date, slash_index);
  std::string first_days = get_days(first_date, slash_index);

  // Finds second_date in date_range
  std::string second_date = date_range.substr(dash_index + 2,
                                              date_range.length());

  // Find slash_index in the second_date
  slash_index = second_date.find("/");

  // Indentify second_month and second_days
  std::string second_month = get_month(second_date, slash_index);
  std::string second_days = get_days(second_date, slash_index);

  // Calling calculate_dur to get duration and then returning it
  int dur = calculate_dur(first_month,first_days,second_month,second_days);
  return dur;
}

// Calculates the largest duration out of all trip durations
int calculate_largest_duration(std::string all_durs, int num_dates)
{
  // Intialize largest_dur, curr_dur, dash_index, and num_dashes_found
  int largest_dur = 0;
  std::string curr_dur = "0"; // this needs to be changed
  int dash_index = 0;
  int num_dashes_found = 0;

  // If num_dates entered is greater than 1, iterate through all durations
  if (num_dates > 1){
    for(size_t i = 0; i < all_durs.size(); i++){
      if(all_durs[i] == '-'){

        // If it is the first duration in all_durs, gets first duration, sets
        // it equal to curr_dur and increment num_dashes_found
        if(num_dashes_found == 0){
          curr_dur = all_durs.substr(dash_index, i);
          ++num_dashes_found;
        }

        // If it is not the first duration in all_durs, gets duration, sets
        // it equal to curr_dur and increment num_dashes_found
        else{
          curr_dur = all_durs.substr(dash_index + 1, i - dash_index - 1);
          ++num_dashes_found;
        }

        // Set dash_index equal to i
        dash_index = i;
      }

      // If it is the last duration in all_durs, get last duration, sets it
      // equal to curr_dur
      else if(num_dashes_found == num_dates - 1)
        curr_dur = all_durs.substr(dash_index + 1, all_durs.size());

      // If curr_dur is larger than largest_dur, set largest_dur equal to
      // curr_dur
      if(std::stoi(curr_dur) > largest_dur)
        largest_dur = std::stoi(curr_dur);
    }
  }

  // If there's 1 duration, set largest_dur equal to that duration
  else
    largest_dur = std::stoi(all_durs);
  return largest_dur;
}

// Calculate smallest duration out of all trip durations
int calculate_smallest_duration(std::string all_durs, int num_dates)
{
  // Intialize smallest_dur, curr_dur, dash_index, and num_dashes_found
  int smallest_dur = 366;
  std::string curr_dur = "366"; // this needs to be changed
  int dash_index = 0;
  int num_dashes_found = 0;

  // If num_dates entered is greater than 1, iterate through all durations
  if (num_dates > 1){
    for(size_t i = 0; i < all_durs.size(); i++){
      if(all_durs[i] == '-'){

        // If it is the first duration in all_durs, gets first duration, sets
        // it equal to curr_dur and increment num_dashes_found
        if(num_dashes_found == 0){
          ++num_dashes_found;
          curr_dur = all_durs.substr(dash_index, i);
        }

        // If it is not the first duration in all_durs, gets duration, sets
        // it equal to curr_dur and increment num_dashes_found
        else{
          ++num_dashes_found;
          curr_dur = all_durs.substr(dash_index + 1, i - dash_index - 1);
        }
        // Set dash_index equal to i
        dash_index = i;
      }

      // If it is the last duration in all_durs, get last duration, sets it
      // equal to curr_dur
      else if(num_dashes_found == num_dates - 1)
        curr_dur = all_durs.substr(dash_index+1, all_durs.size());

      // If curr_dur is smallest than smallest_dur, set smallest_dur equal to
      // curr_dur
      if(std::stoi(curr_dur) < smallest_dur)
        smallest_dur = std::stoi(curr_dur);
    }
  }

  // If there's 1 duration, set largest_dur equal to that duration
  else
    smallest_dur = std::stoi(all_durs);
  return smallest_dur;
}

int main()
{
  int N;                         // number of trips
  std::string date_range;        // a trip description like "1/14--2/27"
  int smallest_dur = 0;     // computed shortest trip
  int largest_dur = 0;      // computed longest trip
  double average_duration = 0.0; // computed averate trip length
  int total_duration = 0;   // number of days away

  // input number of trips:
  std::cin >> N;

  // If there are zero dates, then produce an error message
  if(N == 0){
    std:: cout << "Error, 0 trip dates entered" << std:: endl;
    return 0;
  }

  // input and process each trip:
  int i = 0;
  std:: string all_durs;

  // If number of trips is greater than 0, execute the while loop
  if(N > 0){
    while (i < N) {
     std::cin >> date_range;

     // Add each duration to total_duration and print the duration
     total_duration += separate_dates(date_range);
     std::cout << separate_dates(date_range) << std:: endl;

     // Convert duration to a string and add it to all_durs
     all_durs += std::to_string(separate_dates(date_range));
     ++i;

     // If it is not the last duration, add a dash
     if(i < N){
       all_durs += "-";
     }
   }
 }

  // Get smallest_dur and largest_dur
  smallest_dur = calculate_smallest_duration(all_durs, N);
  largest_dur = calculate_largest_duration(all_durs, N);

  // Calcuate average_duration by dividing total_duration by number of trips
  average_duration = double(total_duration) / N;

  // Output of total days, smallest and largest duration, and average duration
  std::cout << "Total days: " << total_duration << std::endl;
  std::cout << "  Shortest: " << smallest_dur << std::endl;
  std::cout << "   Longest: " << largest_dur << std::endl;
  std::cout << "   Average: " << std::fixed << std::showpoint
            << std::setprecision(2)
              << average_duration << std::endl;

  return 0;
}
