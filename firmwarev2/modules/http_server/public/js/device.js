$(document).ready(function(){
  var WiFiProfile = Backbone.Model.extend({
    idAttribute: "ID"
  });

  var ProfileCollection = Backbone.Collection.extend({
    model: WiFiProfile,
    url: "/networks"
  });

  var ProfileSummaryView = Backbone.View.extend({
    template: _.template($("#profile-summary-template").html()),

    initialize: function(){
      // Modify the model to display how we want it
      this.viewModel = {};
      this.viewModel.ssid = this.model.get("ssid");
      var rssi = this.model.get("ss");
      if(rssi < 121)
        this.viewModel.signalClass = "ss_poor";
      else if(rssi < 141)
        this.viewModel.signalClass = "ss_ok";
      else if(rssi < 161)
        this.viewModel.signalClass = "ss_good";
      else
        this.viewModel.signalClass = "ss_excellent";

      this.viewModel.secured = (this.model.get("apconfig")) & 16 ? true : false;
    },

    render: function(){
      this.$el.html(this.template(this.viewModel));
      return this;
    }
  });

  window.Profiles = new ProfileCollection();

  var NetworkSetupView = Backbone.View.extend({
    el: $("#config-page"),

    events: {
      "click #refresh-networks-btn": "UpdateNetworkList"
    },

    initialize: function(){
      this.listDiv = $("#network-list");
      Profiles.bind("reset", this.UpdateConfigPage, this);
      Profiles.fetch();
    },

    UpdateConfigPage: function(){
      var self = this;
      this.listDiv.empty();
      Profiles.each(function(prof){
        var view = new ProfileSummaryView({model:prof});
        self.listDiv.append(view.render().el);
      });
    },

    UpdateNetworkList: function(){
      $.ajax("/utilities/networkscan", {
        cache: false,
        type: "POST"
      });

      $("#wifi-search-indicator").show();
    },

    Close: function(){
      this.$el.hide();
      clearInterval(this.intervalID);
    },

    Show: function(){
      this.$el.fadeIn(200);
      this.intervalID = setInterval(function(){Profiles.fetch(); $("#wifi-search-indicator").hide();}, 5000);
    }

  });

  var App = Backbone.View.extend({
    el: $("#main-container"),

    events: {
      "click #configure-network-btn": "ConfigureNetwork",
      "click #header-title": "ShowHomePage"
    },

    initialize: function(){

      // Get the available networks
      this.welcomePage = $("#welcome-page");
      this.configPage = new NetworkSetupView();
      this.welcomePage.show();
      this.configPage.Close();

      var self = this;
      $("#header-title").click(function(evnt){
        evnt.preventDefault();
        self.ShowHomePage();
      });
    },

    ConfigureNetwork: function(){
      var page = this.configPage;
      this.welcomePage.fadeOut(300, function(){page.Show();});
    },

    ShowHomePage: function(){
      this.configPage.Close();
      this.welcomePage.fadeIn(200);
    }

  });

  // Start the app
  window.MainApp = new App();
});