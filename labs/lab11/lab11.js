class Lab11 {
  constructor() {}
   //testDefaultParameters
      let jsonObject = [first, second]; 
       allowDefaults(arg1, arg2 = 9) {
        arg1 = jsonObject[1];
        alert("Here are some numbers " + arg1 + arg2);
      }

      //testTemplateLiterals
       templateString(firstName, middleName, lastName) {
        firstName = "Sunjoi";
        middleName = "N/A";
        lastName = "Gandhi";
        var stringTemplate = `${firstName}
                   ${middleName}
                   ${lastName}
       `;
        console.log(stringTemplate);
      }

      //testMultilineStrings
       multilineString() {
        var multiString = `The new season of Love is Blind is out. 
       This is a very messy season,
       I am super invested.
       I do not think Nancy and Bartise will make it 
       `;
        console.log(multiString);
      }

      //testSortWithArrowFunction
      var numArray = [1, 2, 3, 4, 5, 6, 7];
      sortWithArrow(arg1) {
        arg1 = numArray;
        arg1.sort((a, b) => b - a);
        console.log(arg1);
      }
    </script>
}